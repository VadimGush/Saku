//
// Created by tsukuto on 02.04.19.
//

#include <sstream>
#include "Parser.h"
#include "algorithm"
#include "core/kernel/Kernel.h"

using namespace std;

// Удаляет пробелы везде, но не внутри кавычек
void Calc::remove_spaces(string& input) noexcept {
    bool quotation = false;
    input.erase(remove_if(input.begin(), input.end(), [&](auto symbol){
        if (symbol == '\"') quotation = (!quotation);
        return quotation? false : symbol == ' ';
    }), input.end());
}

bool is_valid_symbol(char symbol) noexcept {
    static array<char, 10> valid_symbols{'\"', '(', ')', ',', '.', '_', '='};
    return isalpha(symbol) || isdigit(symbol) || find(valid_symbols.cbegin(), valid_symbols.cend(), symbol) != valid_symbols.end();
}

// Проверяет, что все символы в выражении являются допустимыми
// Если нет, то выкидывает Calc::ParserException
void Calc::is_valid(const string& input) {
    int braces = 0;
    for (auto iterator = input.cbegin(); iterator < input.cend(); iterator++) {
        if (*iterator == '\"') {
            iterator = find(iterator+1, input.cend(), '\"');
            if (iterator == input.cend()) throw Calc::ParserException("незакрытая строка");
        } else {
            if (!is_valid_symbol(*iterator)) throw Calc::ParserException("неизвестный символ");
            else {
                if (*iterator == '(') braces++;
                if (*iterator == ')') braces--;
            }
        }
    }
    if (braces < 0) throw Calc::ParserException("лишняя закрывающая скобка");
    if (braces > 0) throw Calc::ParserException("незакрытая скобка");
}

template <typename Iterator>
Iterator find_last_brace(Iterator begin, Iterator end) {
    int braces = 0;
    bool str = false;
    auto last_braces = find_if(begin, end, [&](auto s){
        if (s == '\"') str = !str;

        if (!str && s == '(') braces ++;
        if (!str && s == ')') braces --;

        return s == ')' && braces == -1;
    });
    return last_braces;
}

// Является ли символ частью допустимого имени переменной или функции
bool Calc::isvar(char symbol) noexcept { return isalpha(symbol) || symbol == '_'; }

// Парсим выражение
shared_ptr<Calc::Object> Calc::parse(string::iterator begin, string::iterator end) {

    if (begin == end) return nullptr;

    auto kernel = Kernel::Instance();

    // Контейнер, который будет наполняться объектами если мы работаем со списком
    unique_ptr<Calc::VectorObject> container;

    auto token = begin;
    while (token != end) {

        shared_ptr<Calc::Object> var;

        // Если первая запятая, то просто бежим вперёд
        if (*token == ',') token++;
        // Если после запятой ничего, то выходим из цикла
        if (token == end) break;

        string debug(token, end);

        // Пытаемся найти конец имени функции или переменной
        auto var_end = find_if(token, end, [](auto symbol){ return !isvar(symbol);});

        if (var_end == token) {
            // Если не нашли имени, значит имеем дело с литералом

            // Если это строка
            if (*token== '\"') {
                auto end_of_string = find(token+1, end, '\"');
                var = make_shared<Calc::StringObject>(string(token+1, end_of_string));
                token = end_of_string+1;
            }

            // Если это число
            if (isdigit(*token) || *token== '.') {
                auto end_of_digit = find_if(token, end, [](auto s){ return !isdigit(s) && s != '.'; });
                var = make_shared<Calc::NumberObject<double>>(stod(string(token,end_of_digit)));
                token = end_of_digit;
            }

            // Если это скобки
            if (*token== '(') {
                auto last_braces = find_last_brace(token+1, end);
                var = parse(token+1, last_braces);
                token = last_braces+1;
            }

        } else {
            // Если нашли, то пытаемся отличить переменную от функции

            if (var_end == end) {
                // Просто переменная
                var = kernel->GetVariable(string(begin, end));

            } else if (var_end+1 == end) {
                // Если после имени стоит символ, то скорее всего это либа незакрытая скобка
                // либо другой символ не на своём месте

                ostringstream information;
                information << "ожидается () после " << string(begin, var_end) << ", а не \'" << *var_end << "\'";
                throw ParserException(information.str());
            } else {
                // здесь вызов функции
            }
        }

        // Складываем объект в контейнер
        if (var != nullptr) {
            if (container == nullptr) container = make_unique<Calc::VectorObject>();
            container->GetVector().push_back(var);
        }

        // Если на конце не запятая, значит это не перечисление
        if (token != end && *token != ',') break;

    }

    if (container == nullptr) return nullptr;
    else if (container->GetVector().size() == 1) return container->GetVector()[0];
    else return container;
}



//
// Created by tsukuto on 02.04.19.
//

#include <sstream>
#include "Parser.h"
#include "algorithm"
#include "core/kernel/Kernel.h"

using namespace std;

// Удаляет пробелы везде, но не внутри кавычек
void Calc::remove_spaces(string& input) {
    bool quotation = false;
    input.erase(remove_if(input.begin(), input.end(), [&](auto symbol){
        if (symbol == '\"') quotation = (!quotation);
        return quotation? false : symbol == ' ';
    }), input.end());
}

// Является ли символ частью допустимого имени переменной или функции
bool Calc::isvar(char symbol) noexcept { return isalpha(symbol) || symbol == '_'; }

// Парсим выражение
shared_ptr<Calc::Object> Calc::parse(string::iterator begin, string::iterator end) {

    if (begin == end) throw ParserException("пустое выражение");

    auto kernel = Kernel::Instance();

    // Создаём локальную временную переменную
    shared_ptr<Calc::Object> var;

    // Получаем первый токен
    auto first_token = find_if(begin, end, [](auto symbol) { return !isvar(symbol); });

    if (first_token == begin) {
        // Значит токена нет

    } else {
        if (first_token==end) {
            // У нас только одно значение
            var = kernel->GetVariable(string(begin, end));
        } else if (first_token+1 == end) {
            // какое-то имя и один единственный символ на конце
            if (*first_token == '(') throw ParserException("незакрытая скобка");
            else if (*first_token == ',') var = kernel->GetVariable(string(begin,first_token));
            else {
                ostringstream info;
                info << "неизвестный символ \'" << *first_token << '\'';
                throw ParserException(info.str());
            }
        }
    }

    // Возвращаем переменную
    return var;
}



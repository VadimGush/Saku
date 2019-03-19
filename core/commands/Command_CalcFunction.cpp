//
// Created by tsukuto on 19.03.19.
//

#include "Command_CalcFunction.h"
#include <sstream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <chrono>
using namespace Calc;

// Список доступных операторов (порядок операторов определяет их приоритет в порядке возрастания)
const std::array<char, 5> operators{'+', '-', '/', '*', '^'};
// Список доступных функций
// const std::array<std::string, 10> functions{"sin", "cos", "exp", "sqrt"};

// Ошибка парсинга функции
struct ParsingException : public std::exception {
    explicit ParsingException(std::string what) : what_{std::move(what)} {}

    const char* what() const noexcept override {
        return what_.c_str();
    }
private:
    std::string what_;
};

// Типы элементов, которые мы можем встретить внутри функции
enum class Type { NOTHING, OPERATOR, VARIABLE, NUMBER, PARENTHESES};

// Элемент функции
struct Object{
    Type type;
};

// Оператор
struct Operator : Object {
    explicit Operator(char noper) : Object{Type::OPERATOR}, oper{noper} {}
    char oper;
};

// Переменная
struct Variable : Object {
    explicit Variable(std::string vname) : Object{Type::VARIABLE}, name{std::move(vname)} {}
    std::string name;
};

// Число
struct Number : Object {
    explicit Number(double nvalue) : Object{Type::NUMBER}, value{nvalue} {}
    double value;
};

// Скобка
struct Parentheses : Object {
    Parentheses() : Object{Type::PARENTHESES} {}
};

static void handle_token(std::stringstream& token, Type type, std::vector<Object>& operator_stack, std::vector<Object>& stack) {
    switch (type) {
        case Type::VARIABLE:
            stack.push_back(Variable{token.str()});
            break;
        case Type::NUMBER:
            double value;
            token >> value;
            stack.push_back(Number{value});
            break;
        default:
            break;
    }
}

class Function {
public:
    explicit Function(std::string& input) {
        using namespace std;

        // Shunting-yard algorithm
        // TODO: Оптимизировать код если возможно

        vector<Object> operator_stack;

        // Текущий токен
        Type token_type = Type::NOTHING;
        stringstream token;

        auto iterator = input.begin();

        while (iterator != input.end()) {
            char symbol = *iterator;
            Type last_token_type = token_type;

            ++iterator;
            if (symbol == ' ') continue;

            if (isdigit(symbol) || symbol == '.') {
                // Если цифра или точка, значит мы читаем число
                token_type = Type::NUMBER;
            }
            else if (isalpha(symbol)) {
                // Если буква, значит это будет либо переменная либо функция
                token_type = Type::VARIABLE;
            }
            else if (symbol == '(') {
                // Если прошлым токеном было что-то символьное и мы встретили открывающую скобку
                // следовательно мы имеем дело с функцией
                if (last_token_type == Type::VARIABLE)
                    last_token_type = Type::OPERATOR;
                // Скобку как отдельный элемент мы обрабатываем в любом случае
                token_type = Type::PARENTHESES;
            }
            else if (find(operators.begin(), operators.end(), symbol) != operators.end()) {
                // Если оператор, значит оператор
                token_type = Type::OPERATOR;
            }
            else {
                ostringstream information;
                information << input << endl;
                information << setw(static_cast<int>(iterator - input.begin())) << "^";
                throw ParsingException{information.str()};
            }

            // Если новый токен не равен предыдущему, значит прошлый необходимо обработать
            if (last_token_type != Type::NOTHING && last_token_type != token_type) {
                handle_token(token, last_token_type, operator_stack, stack_);
                token = stringstream{};
            }

            // И записываем токен нового символа
            token << symbol;
        }
        // Не забываем обработать последний токен
        handle_token(token, token_type, operator_stack, stack_);
    }

private:

    std::map<std::string, double> variables_{
        {"pi",3.14}
    };

    std::vector<Object> stack_;
};

void Command_CalcFunction::Handle(std::istream& input, std::ostream& output) {
    using namespace std;
    string function_string;
    output << "Функция: ";
    input >> function_string;

    try {
        Function function{function_string};
    } catch (ParsingException& exception) {
        output << "Синтаксическая ошибка:" << endl;
        output << exception.what() << endl;
    }
}

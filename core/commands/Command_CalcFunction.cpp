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
#include <memory>
using namespace Calc;

// Список доступных операторов (порядок операторов определяет их приоритет в порядке возрастания)
static std::array<char, 5> operators{'+', '-', '/', '*', '^'};
// Список доступных функций
static std::array<std::string, 4> functions{"sin", "cos", "exp", "sqrt"};

struct ParsingException : public std::exception {
    explicit ParsingException(std::string what) : what_{std::move(what)} {}

    const char* what() const noexcept override {
        return what_.c_str();
    }
private:
    std::string what_;
};

// Типы элементов, которые мы можем встретить внутри функции
enum class Type { NOTHING, OPERATOR, VARIABLE, NUMBER, PAREN_LEFT, PAREN_RIGHT, FUNCTION};
enum class Associativity { RIGHT, LEFT };

// Элемент функции
struct Object{
    explicit Object(Type ntype) : type{ntype} {}
    Type type;
};

struct Operator : Object {
    explicit Operator(char noper, int nprec) : Object{Type::OPERATOR}, oper{noper}, prec{nprec} {}
    char oper;  // оператор
    int prec;   // приоритет
    Associativity asc = Associativity::LEFT;
};

struct ObjectFunction : Object {
    explicit ObjectFunction(std::string fname) : Object{Type::FUNCTION}, name{std::move(fname)} {}
    std::string name;
};

struct Variable : Object {
    explicit Variable(std::string vname) : Object{Type::VARIABLE}, name{std::move(vname)} {}
    std::string name;
};

struct Number : Object {
    explicit Number(double nvalue) : Object{Type::NUMBER}, value{nvalue} {}
    double value;
};

static void handle_token(
        std::stringstream& token,
        Type type, std::vector<std::shared_ptr<Object>>& operator_stack,
        std::vector<std::shared_ptr<Object>>& stack) {

    using namespace std;
    cout << token.str() << endl;
    if (type == Type::VARIABLE) {
        stack.push_back(make_shared<Variable>(token.str()));
    }
    else if (type == Type::NUMBER) {
        double value;
        token >> value;
        stack.push_back(make_shared<Number>(value));
    }
    else if (type == Type::FUNCTION) {
        string function_name = token.str();
        if (find(functions.begin(), functions.end(), function_name) == functions.end())
            throw ParsingException("Неизвестная функция: " + token.str() + "()");
        operator_stack.push_back(make_shared<ObjectFunction>(function_name));
    }
    else if (type == Type::OPERATOR) {
        char opr_char = token.str()[0];
        // Создаём текущий оператор
        auto opr = make_shared<Operator>(opr_char,
                                         find(operators.begin(), operators.end(), opr_char) - operators.begin());
        // Если это возведение в степень, то ассоциативность правая
        if (opr_char == '^') opr->asc = Associativity::RIGHT;
        // Если стэк операторов не пустой
        if (!operator_stack.empty()) {
            // Берём оператор сверху
            auto top = operator_stack.back();
            // АААА, ЛУЧШЕ ЭТОТ КОД НИКОМУ НЕ ВИДЕТЬ
            while (
                    (top->type == Type::FUNCTION) ||
                    (top->type == Type::OPERATOR && static_pointer_cast<Operator>(top)->prec > opr->prec) ||
                    (top->type == Type::OPERATOR && static_pointer_cast<Operator>(top)->prec == opr->prec
                    && static_pointer_cast<Operator>(top)->asc == Associativity::LEFT) &&
                    (top->type != Type::PAREN_LEFT)
                    )
            {
                stack.push_back(top);
                operator_stack.pop_back();
                if (operator_stack.empty()) break;
                // Переходим к следующему
                top = operator_stack.back();
            }
        }
        // Наконец-то вставляем оператор
        operator_stack.push_back(opr);
    }
    else if (type == Type::PAREN_LEFT) {
        operator_stack.push_back(make_shared<Object>(Type::PAREN_LEFT));
    }
    else if (type == Type::PAREN_RIGHT) {
        if (!operator_stack.empty()) {
            auto top = operator_stack.back();
            while (top->type != Type::PAREN_LEFT) {
                stack.push_back(top);
                operator_stack.pop_back();
                if (operator_stack.empty()) break;
                top = operator_stack.back();
            }
            if (!operator_stack.empty() && (operator_stack.back()->type == Type::PAREN_LEFT))
                operator_stack.pop_back();
            else
                throw ParsingException("Незакрытые скобки");
        }
    }

}

class Function {
public:
    explicit Function(std::string& input) {
        using namespace std;

        // Shunting-yard algorithm
        // TODO: Оптимизировать код если возможно

        vector<shared_ptr<Object>> operator_stack;

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
                    last_token_type = Type::FUNCTION;
                // Скобку как отдельный элемент мы обрабатываем в любом случае
                token_type = Type::PAREN_LEFT;
            }
            else if (symbol == ')') {
                token_type = Type::PAREN_RIGHT;
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

        for (const auto& element : operator_stack)
            stack_.push_back(element);

        cout << "== STACK ==" << endl;
        for (const auto& element : stack_) {
            if (element->type == Type::VARIABLE) cout << "VARIABLE" << endl;
            else if (element->type == Type::NUMBER) cout << "NUMBER" << endl;
            else if (element->type == Type::FUNCTION) cout << "FUNCTION" << endl;
            else if (element->type == Type::OPERATOR) cout << "OPERATOR" << endl;
        }
    }

private:

    std::map<std::string, double> variables_{
        {"pi",3.14}
    };

    std::vector<std::shared_ptr<Object>> stack_;
};

void Command_CalcFunction::Handle(std::istream& input, std::ostream& output) {
    using namespace std;
    string function_string;
    output << "Функция: ";
    getline(input, function_string);

    try {
        Function function{function_string};
    } catch (ParsingException& exception) {
        output << "Синтаксическая ошибка:" << endl;
        output << exception.what() << endl;
    }
}

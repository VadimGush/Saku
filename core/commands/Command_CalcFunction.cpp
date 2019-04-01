#include "Command_CalcFunction.h"
#include <sstream>
#include <vector>
#include <map>
#include <array>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <memory>
using namespace Calc;

// Список доступных операторов (порядок операторов определяет их приоритет в порядке возрастания)
static const std::array<char, 5> operators{'+', '-', '/', '*', '^'};
// Список доступных функций
static const std::array<std::string, 4> functions{"sin", "cos", "exp", "sqrt"};
// Типы элементов математического выражения
enum class Type { NOTHING, OPERATOR, VARIABLE, NUMBER, PAREN_LEFT, PAREN_RIGHT, FUNCTION};
// Типы ассоциативности операторов мат. выражения
enum class Associativity { RIGHT, LEFT };

struct ParsingException : public std::exception {
    explicit ParsingException(std::string what) : what_{std::move(what)} {}

    const char* what() const noexcept override {
        return what_.c_str();
    }
private:
    std::string what_;
};

// Элемент математического выражения
struct Element {
    explicit Element(Type ntype) : type{ntype} {}
    Type type;
};

struct Operator : Element {
    explicit Operator(char noper, int nprec) : Element{Type::OPERATOR}, oper{noper}, prec{nprec} {}
    char oper;  // оператор
    int prec;   // приоритет
    Associativity asc = Associativity::LEFT;
};

struct ElementFunction : Element {
    explicit ElementFunction(std::string fname) : Element{Type::FUNCTION}, name{std::move(fname)} {}
    std::string name;
};

struct Variable : Element {
    explicit Variable(std::string vname) : Element{Type::VARIABLE}, name{std::move(vname)} {}
    std::string name;
};

struct Number : Element {
    explicit Number(double nvalue) : Element{Type::NUMBER}, value{nvalue} {}
    double value;
};

// Получаем некоторый токен мат. выражения в виде строки и формируем из него элемент в одном из стеков
static void handle_token(
        std::stringstream& token,
        Type type, std::vector<std::shared_ptr<Element>>& operator_stack,
        std::vector<std::shared_ptr<Element>>& stack) {

    using namespace std;
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
        operator_stack.push_back(make_shared<ElementFunction>(function_name));
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
        operator_stack.push_back(make_shared<Element>(Type::PAREN_LEFT));
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

        vector<shared_ptr<Element>> operator_stack;

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
                information << setw(static_cast<int>(iterator - input.begin())) << "^" << endl;
                information << "Неизвестный символ";
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

        // Перемещаем все оставшиеся элементы из стека операторов в общий стек
        for (const auto& element : operator_stack)
            stack_.push_back(element);
    }

    double Run() const {
        // Подсчитывает значение функции
        return 0;
    }

    const std::map<std::string, double>& GetVariable() { return variables_; };
private:
    std::map<std::string, double> variables_{ {"pi",3.14} };
    std::vector<std::shared_ptr<Element>> stack_;
};

/*
void Command_CalcFunction::Run() {
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
 */

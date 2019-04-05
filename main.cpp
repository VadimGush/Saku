#include <iostream>
#include <algorithm>
#include <sstream>
#include "configure.h"
#include "core/commands/CommandManager.h"
#include "core/kernel/objects/Object.h"
#include "core/kernel/objects/FileObject.h"
#include "Parser.h"
using namespace std;

// Форматированный ввод строки
istream& getln(istream& input, string& command) {
    cout << "\e[34;1m" << ">>> " << "\e[0m";
    return getline(cin, command);
}

int main() {

    cout << endl << " \e[1m\e[35;1mSaku\e[0m - программа для параллельных вычислений" << endl;
    cout << " \e[1mВерсия:\e[0m " << VERSION << endl << endl;

    auto kernel = Calc::Kernel::Instance();
    auto manager = Calc::CommandManager::Instance();

    kernel->AssignVariable("pi", make_shared<Calc::NumberObject<double>>(3.14));
    kernel->AssignVariable("author", make_shared<Calc::StringObject>("Vadim Gush"));
    kernel->AssignVariable("text", make_shared<Calc::FileObject>("Makefile"));
    kernel->AssignVariable("arg", make_shared<Calc::ValueObject<double>>("x", 3.14));

    auto vec = make_shared<Calc::VectorObject>();
    kernel->AssignVariable("vec", vec);

    // TODO: Переместить всю эту кашу с парсингом в Parser.cpp

    for (string command; getln(cin, command);) {

        Calc::remove_spaces(command);
        try {
            Calc::is_valid(command);
        } catch (const std::exception& e) {
            cout << "Недопустимый ввод: " << e.what() << endl;
            continue;
        }
        if (command.empty()) continue;
        if (command == "exit") break;

        // Получаем итератор на конец первого токена (имя функции или переменной)
        auto first_token = find_if(command.begin(), command.end(), [](auto symbol) { return !Calc::isvar(symbol); });

        // Если этот токен это вся строка
        if (first_token == command.end()) {

            try {
                // Либо ищем команду и выполняем её
                auto cmd = manager->GetCommand(command);
                cmd->Run(cout);
            } catch (out_of_range &) {

                // Либо выводим информацию о переменной
                try {
                    auto var = kernel->GetVariable(command);
                    var->operator<<(cout) << endl;
                } catch (out_of_range&) {
                    cout << "Переменная " << command << " не найдена" << endl;
                }

            }
        } else {
            auto next_symbol = *first_token;

            try {
                if (next_symbol == '=') {

                    // Не допускаем, чтобы пользователь создал переменную совпадающую с именем
                    // одной из достпуных комманд
                    string variable_name(command.begin(), first_token);
                    if (manager->GetCommandMap().count(variable_name) != 0 || variable_name == "exit") {
                        cout << "Ошибка: имя переменной совпадает с командой" << endl;
                        cout << "    " << variable_name << " - " << manager->GetCommand(variable_name)->GetDescription() << endl;
                        continue;
                    }

                    // Парсим выражение слева от знака равно
                    auto var = Calc::parse(first_token+1, command.end());
                    // Вставляем новое значение в переменную
                    if (var != nullptr) kernel->AssignVariable(string(command.begin(), first_token), var);

                } else if (next_symbol == '(' || next_symbol == ',' || next_symbol == '\"') {

                    // TODO: Парсить надо в любом случае

                    // Парсим выражение
                    auto temp = Calc::parse(command.begin(), command.end());
                    // Если у выражения есть результат, то выводим его
                    if (temp != nullptr) temp->operator<<(cout) << endl;

                } else
                    cout << "Неизвестный символ: " << next_symbol << endl;
            } catch (exception& exception) {
                // Здесь мы можем отловить либо ParserException если в выражении ошибка либо
                // PlatformNotSupported если одна из функций не поддерживается на текущей платформе
                cout << "Ошибка: " << exception.what() << endl;
            }
        }
    }

    return 0;
}
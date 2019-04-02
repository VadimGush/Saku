#include <iostream>
#include <algorithm>
#include <sstream>
#include "configure.h"
#include "core/commands/CommandManager.h"
#include "core/kernel/objects/Object.h"
#include "Parser.h"
using namespace std;

// Форматированный ввод строки
istream& getln(istream& input, string& command) {
    cout << ">>> "; return getline(cin, command);
}

int main() {

    cout << endl << " Saku - программа для параллельных вычислений" << endl;
    cout <<" Версия: " << VERSION << endl << endl;

    auto kernel = Calc::Kernel::Instance();
    auto manager = Calc::CommandManager::Instance();

    for (string command; getln(cin, command);) {

        Calc::remove_spaces(command);
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
                    cout << var << endl;
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
                    if (manager->GetCommandMap().count(variable_name) != 0) {
                        cout << "Ошибка: имя переменной совпадает с командой" << endl;
                        cout << "    " << variable_name << " - " << manager->GetCommand(variable_name)->GetDescription() << endl;
                        continue;
                    }

                    // Парсим выражение слева от знака равно
                    auto var = Calc::parse(first_token+1, command.end());
                    // Вставляем новое значение в переменную
                    if (var != nullptr) kernel->AssignVariable(string(command.begin(), first_token), var);

                } else if (next_symbol == '(' || next_symbol == ',' || next_symbol == '\"') {

                    // Парсим выражение
                    auto temp = Calc::parse(command.begin(), command.end());
                    // Если у выражения есть результат, то выводим его
                    if (temp != nullptr) cout << temp << endl;

                } else
                    cout << "Неизвестный символ: " << next_symbol << endl;
            } catch (exception& exception) {
                // Здесь мы можем отловить либо ParserException если в выражении ошибка либо
                // PlatformNotSupported если одна из функций не поддерживается на текущей платформе
                cout << exception.what() << endl;
            }
        }
    }

    return 0;
}
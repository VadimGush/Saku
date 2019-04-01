#include <iostream>
#include <algorithm>
#include <sstream>
#include "configure.h"
#include "core/CommandManager.h"
using namespace std;

// Удаляет пробелы везде, но не внутри кавычек
void remove_spaces(string& input) {
    bool quotation = false;
    input.erase(remove_if(input.begin(), input.end(), [&](auto symbol){
        if (symbol == '\"') quotation = (!quotation);
        return quotation? false : symbol == ' ';
    }), input.end());
}

// Является ли символ частью допустимого имени переменной или функции
bool isvar(char symbol) { return isalpha(symbol) || symbol == '_'; }

// Парсим пользовательский ввод
template <class Iterator>
void parse(Iterator begin, Iterator end) {
    // Получаем первый токен
    auto first_token = find_if(begin, end, [](auto symbol){ return !isvar(symbol); });
}

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

        remove_spaces(command);
        if (command.empty()) continue;
        if (command == "exit") break;

        // Получаем итератор на конец первого токена (имя функции или переменной)
        auto first_token = find_if(command.begin(), command.end(), [](auto symbol) { return !isvar(symbol); });

        // Если этот токен это вся строка
        if (first_token == command.end()) {
            // Значит пользователь хочет выполнить команду или вывести информацию о переменной
            try {
                auto cmd = manager->GetCommand(command);
                cmd->Run(cout);
            } catch (out_of_range &) {
                // Поиск перменной

                // Вывод информации о переменной

                cout << "Команда/переменная не найдена" << endl;
            }
        } else {
            auto next_symbol = *(first_token);

            if (next_symbol == '=') {
                // Присваение

                // Создаём и получаем указатель на переменную

                // Вызываем функцию

            } else if (next_symbol == '(') {
                // Заводим временную переменную

                // Вызов функции

                // Выводим информацию о переменной
            } else
                cout << "Неизвестный символ: " << next_symbol << endl;
        }
    }

    return 0;
}
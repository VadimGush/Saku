#include <iostream>
#include "core/CommandManager.h"
using namespace std;

int main() {

    // Инициализируем ядро
    Calc::Kernel* kernel = Calc::Kernel::Instance();
    kernel->init(cout);

    // Инициализируем менеджер команд
    Calc::CommandManager* manager = Calc::CommandManager::Instance();

    const string prefix = ">>> ";
    cout << prefix;

    for (string command; cin >> command;) {

        // Выходит из терминала
        if (command == "exit") break;

        try {
            // Получаем команду по имени и пытаемся её выполнить
            shared_ptr<Calc::Command> state = manager->GetCommand(command);
            try {
                state->Handle(cin, cout);
            } catch (Calc::PlatformNotSupported&) {
                cout << "Операция не поддерживает текущую платформу" << endl;
            }
        } catch (out_of_range&) {
            cout << "Комманда не найдена" << endl;
        }

        cout << prefix;
    }

    return 0;
}
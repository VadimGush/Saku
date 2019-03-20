#include <iostream>
#include "configure.h"
#include "core/CommandManager.h"
using namespace std;

int main() {

    cout << "Saku " << VERSION << endl;

    Calc::CommandManager* manager = Calc::CommandManager::Instance();

    cout << ">>> ";
    for (string command; cin >> command; ) {

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
        cout << ">>> ";
    }

    return 0;
}
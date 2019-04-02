#include "Command_Help.h"
#include "CommandManager.h"
#include <iomanip>

using namespace Calc;

void Print(std::ostream& output, const std::string& name, const std::string& description) {
    output << " \e[1m" << std::setw(15) << std::left << name << "\e[0m - " << description << std::endl;
}

void Command_Help::Run(std::ostream& output) {
    output << "Список доступных команд: " << std::endl;
    CommandManager* manager = CommandManager::Instance();
    for (const auto& cmd : manager->GetCommandMap()) {
        Print(output, cmd.first, cmd.second->GetDescription());
    }
    Print(output, "exit", "выход из программы");
}
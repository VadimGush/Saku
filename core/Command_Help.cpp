//
// Created by tsukuto on 15.03.19.
//

#include "Command_Help.h"
#include "CommandManager.h"

using namespace Calc;

void Command_Help::Handle(std::istream&, std::ostream& output) {
    output << "Список доступных команд: " << std::endl;
    CommandManager* manager = CommandManager::Instance();
    for (const auto& cmd : manager->GetCommandMap()) {
        output << " \e[1m" << cmd.first << "\e[0m\t - " << cmd.second->GetDescription() << std::endl;
    }
    output << " " << "\e[1mexit\e[0m\t - выйти из программы" << std::endl;
}
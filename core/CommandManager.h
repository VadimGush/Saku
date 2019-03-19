//
// Created by tsukuto on 15.03.19.
//

#ifndef CALC_COMMANDMANAGER_H
#define CALC_COMMANDMANAGER_H

#include "commands/Command.h"
#include "commands/Command_Help.h"
#include "commands/Command_KernelInfo.h"
#include "commands/Command_Pow.h"
#include "commands/Command_Settings.h"
#include "commands/Command_CalcFunction.h"
#include <map>
#include <string>
#include <memory>

namespace Calc {

    // Хранит в себе экземпляры всех доступных команд
    class CommandManager {
    public:
        static CommandManager* Instance();

        // Получить команду по её имени
        std::shared_ptr<Command> GetCommand(const std::string& command) const;

        // Полные список команд
        const std::map<std::string, std::shared_ptr<Command>>& GetCommandMap() const;

    private:

        CommandManager() =default;

        const std::map<std::string, std::shared_ptr<Command>> commands_ = {
                {"help", std::make_shared<Command_Help>()},
                {"kernel", std::make_shared<Command_KernelInfo>()},
                {"pow", std::make_shared<Command_Pow>()},
                {"settings", std::make_shared<Command_Settings>()},
                {"calc_function", std::make_shared<Command_CalcFunction>()}
        };

        static CommandManager* instance_;
    };
}


#endif //CALC_COMMANDMANAGER_H

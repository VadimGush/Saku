//
// Created by tsukuto on 15.03.19.
//

#ifndef CALC_COMMANDMANAGER_H
#define CALC_COMMANDMANAGER_H

#include "Command.h"
#include "Command_Help.h"
#include "Command_KernelInfo.h"
#include "Command_CalcFunction.h"
#include "Command_Variables.h"
#include <map>
#include <string>
#include <memory>

namespace Calc {

    // Хранит в себе экземпляры всех доступных команд.
    // Позволяет получать доступ к списку команд для их вывода, автодополнения или поиска.
    class CommandManager {
    public:
        static std::shared_ptr<CommandManager> Instance();

        // Получить команду по её имени
        std::shared_ptr<Command> GetCommand(const std::string &command) const;

        // Полный список команд
        const std::map<std::string, std::shared_ptr<Command>> &GetCommandMap() const;

    private:

        CommandManager() = default;

        const std::map<std::string, std::shared_ptr<Command>> commands_ = {
                {"help",      std::make_shared<Command_Help>()},
                {"kernel",    std::make_shared<Command_KernelInfo>()},
                {"variables", std::make_shared<Command_Variables>()}
        };

        static std::shared_ptr<CommandManager> instance_;
    };
}


#endif //CALC_COMMANDMANAGER_H

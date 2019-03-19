//
// Created by tsukuto on 19.03.19.
//

#ifndef SAKU_COMMAND_SETTINGS_H
#define SAKU_COMMAND_SETTINGS_H


#include "Command.h"

namespace Calc {
    class Command_Settings : public Command {
    public:
        Command_Settings() : Command("настройка ядра") {}

        void Handle(std::istream&, std::ostream&) override;
    };
}


#endif //SAKU_COMMAND_SETTINGS_H

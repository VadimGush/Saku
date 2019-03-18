//
// Created by tsukuto on 15.03.19.
//

#ifndef CALC_COMMAND_HELP_H
#define CALC_COMMAND_HELP_H

#include "Command.h"

namespace Calc {
    class Command_Help : public Command {
    public:
        Command_Help() : Command("вывод справки") {}

        void Handle(std::istream& input, std::ostream& output) override;
    };
}


#endif //CALC_COMMAND_HELP_H

//
// Created by tsukuto on 18.03.19.
//

#ifndef CALC_COMMAND_POW_H
#define CALC_COMMAND_POW_H

#include "Command.h"

namespace Calc {
    class Command_Pow : public Command {
    public:
        Command_Pow() : Command("возведение в степень") {}

        void Handle(std::istream& input, std::ostream& output) override;
    };
}


#endif //CALC_COMMAND_POW_H

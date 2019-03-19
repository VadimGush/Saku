//
// Created by tsukuto on 19.03.19.
//

#ifndef SAKU_COMMAND_CALCFUNCTION_H
#define SAKU_COMMAND_CALCFUNCTION_H


#include "Command.h"

namespace Calc {
    class Command_CalcFunction : public Command {
    public:
        Command_CalcFunction() : Command("вычисление значения заданной функции") {}

        void Handle(std::istream&, std::ostream&) override;
    };
}


#endif //SAKU_COMMAND_CALCFUNCTION_H

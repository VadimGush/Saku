#ifndef SAKU_COMMAND_CALCFUNCTION_H
#define SAKU_COMMAND_CALCFUNCTION_H


#include "Command.h"

namespace Calc {
    class Command_CalcFunction : public Command {
    public:
        Command_CalcFunction() : Command("вычисление значения заданной функции") {}

        void Run(std::ostream &) override;
    };
}


#endif //SAKU_COMMAND_CALCFUNCTION_H

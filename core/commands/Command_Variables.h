//
// Created by tsukuto on 02.04.19.
//

#ifndef SAKU_COMMANDVARIABLES_H
#define SAKU_COMMANDVARIABLES_H

#include "Command.h"

namespace Calc {
    class Command_Variables : public Command {
    public:
        Command_Variables() : Command("список переменных") {}

        void Run(std::ostream&) override;
    };
}


#endif //SAKU_COMMANDVARIABLES_H

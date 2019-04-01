#ifndef CALC_COMMAND_HELP_H
#define CALC_COMMAND_HELP_H

#include "Command.h"

namespace Calc {
    class Command_Help : public Command {
    public:
        Command_Help() : Command("вывод справки") {}

        void Run(std::ostream&) override;
    };
}


#endif //CALC_COMMAND_HELP_H

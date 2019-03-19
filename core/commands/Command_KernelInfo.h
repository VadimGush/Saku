//
// Created by tsukuto on 18.03.19.
//

#ifndef CALC_COMMAND_KERNELINFO_H
#define CALC_COMMAND_KERNELINFO_H

#include "Command.h"
#include "../kernel/Kernel.h"

namespace Calc {
    class Command_KernelInfo : public Command {
    public:
        Command_KernelInfo() : Command("информация о ядре (список платформ)") {}

        void Handle(std::istream& input, std::ostream& output) override;
    };
}


#endif //CALC_COMMAND_KERNELINFO_H

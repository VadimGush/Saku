//
// Created by tsukuto on 18.03.19.
//

#include "Command_Pow.h"
#include "functions/Function_Pow.h"
#include "kernel/Kernel.h"

using namespace Calc;

void Command_Pow::Handle(std::istream& input, std::ostream& output) {
    double base, power;
    output << "Основание: ";
    input >> base;
    output << "Степень: ";
    input >> power;

    Function_Pow function(base, power);
    Kernel::Instance()->GetPlatform()->Handle(function, output);
}
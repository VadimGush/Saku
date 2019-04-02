//
// Created by tsukuto on 02.04.19.
//

#include "Command_Variables.h"
#include "../kernel/Kernel.h"
#include <iomanip>

using namespace Calc;

void Command_Variables::Run(std::ostream& output) {
    auto kernel = Kernel::Instance();

    if (kernel->GetVariables().empty()) {
        output << "Переменные отсутствуют" << std::endl;
        return;
    }

    output << "Переменные:" << std::endl;

    for (auto& var: kernel->GetVariables()) {
        output << " \e[33m" << std::setw(7) << std::left;
        switch(var.second->GetType()) {
            case ObjectType::FILE: output << "file"; break;
            case ObjectType::NUMBER: output << "number"; break;
            case ObjectType::VECTOR: output << "vector"; break;
            case ObjectType::VALUE: output << "value"; break;
            case ObjectType::STRING: output << "string"; break;
        }
        output << "\e[0m";
        output << " " << std::setw(10) << std::left << var.first << " = ";
        var.second->operator<<(output);
        output << std::endl;
    }
}

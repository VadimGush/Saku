//
// Created by tsukuto on 19.03.19.
//

#include "Command_Settings.h"
#include "../kernel/Kernel.h"

using namespace Calc;

void Command_Settings::Handle(std::istream& input, std::ostream& output) {
    unsigned long platform_id;
    output << "Текущая платформа: ";
    input >> platform_id;
    Kernel* kernel = Kernel::Instance();
    kernel->SetPlatform(platform_id);
    output << "Выбрана " << kernel->GetPlatform()->GetName() << std::endl;
}
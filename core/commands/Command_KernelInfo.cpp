#include "Command_KernelInfo.h"
#include "../kernel/Kernel.h"

using namespace Calc;

void Command_KernelInfo::Run(std::ostream& output) {
    auto kernel = Kernel::Instance();

    output << "Список доступных платформ:" << std::endl;
    int id = 0;
    for (const auto& platform : kernel->GetPlatforms()) {
        if (kernel->GetPlatform() == platform)
            output << " --> ";
        else
            output << "     ";
        output << "[" << id << "] " <<  platform->GetName();
        output << std::endl;
        id++;
    }
}
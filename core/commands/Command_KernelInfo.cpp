#include "Command_KernelInfo.h"

using namespace Calc;

void Command_KernelInfo::Run(std::ostream &output) {
    using namespace std;
    auto kernel = Kernel::Instance();

    output << "Параметры ядра:" << endl;
    output << " Кеширование: " << (kernel->IsCache() ? "включено" : "выключено") << endl;
    output << endl;

    output << "Состояние кеша:" << endl;
    output << " Количество объектов: " << kernel->CacheLength() << endl;
    output << " Размер кеша: ~" << kernel->CacheSize() << " байт" << endl;
    output << endl;

    output << "Список доступных платформ:" << endl;
    int id = 0;
    for (const auto &platform : kernel->GetPlatforms()) {
        if (kernel->GetPlatform() == platform)
            output << " --> ";
        else
            output << "     ";
        output << "[" << id << "] " << platform->GetName();
        output << endl;
        id++;
    }
}
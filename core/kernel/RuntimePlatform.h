#ifndef CALC_RUNTIMEPLATFORM_H
#define CALC_RUNTIMEPLATFORM_H

#include "Platform.h"
#include "../operations/Operation.h"
#include <memory>
#include <iostream>

namespace Calc {
    // Не является платформой как таковой. Отвечает за вычисления, которые можно
    // выполнить непосредственно внутри программы.
    class RuntimePlatform : public Platform {
    public:
        RuntimePlatform() : Platform("Runtime Platform") {}

        void Handle(Operation &operation) override {
            operation.Calculate(*this);
        }
    };
}


#endif //CALC_RUNTIMEPLATFORM_H

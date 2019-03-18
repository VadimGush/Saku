//
// Created by tsukuto on 18.03.19.
//

#ifndef CALC_RUNTIMEPLATFORM_H
#define CALC_RUNTIMEPLATFORM_H

#include "Platform.h"
#include "../functions/Function.h"
#include <memory>
#include <iostream>

namespace Calc {
    // Не является платформой как таковой. Отвечает за вычисления, которые можно
    // выполнить непосредственно внутри программы.
    class RuntimePlatform : public Platform {
    public:
        RuntimePlatform() : Platform("Runtime Platform") {}

        void Handle(Function &function, std::ostream &output) override;
    };
}


#endif //CALC_RUNTIMEPLATFORM_H

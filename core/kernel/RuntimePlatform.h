#ifndef CALC_RUNTIMEPLATFORM_H
#define CALC_RUNTIMEPLATFORM_H

#include "Platform.h"
#include "operations/Operation.h"
#include <memory>
#include <iostream>

namespace Calc {
    // RuntimePlatform - стандартная платформа, которая не закреплена за каким-либо устройством и используемая
    // для вычислений внутри программы.
    class RuntimePlatform : public Platform {
    public:
        RuntimePlatform() : Platform("Runtime Platform") {}

        std::unique_ptr<Object> Handle(Operation &operation) override {
            return operation.Calculate(*this);
        }
    };
}


#endif //CALC_RUNTIMEPLATFORM_H

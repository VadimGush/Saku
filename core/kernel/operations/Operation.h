#ifndef CALC_FUNCTION_H
#define CALC_FUNCTION_H

#include <iostream>
#include <exception>
#include <memory>
#include "../objects/Object.h"

namespace Calc {

    class RuntimePlatform;
    class CPUPlatform;

    // Если операция не поддерживает выполнение на текущей платформе
    struct PlatformNotSupported : public std::exception {
        const char * what() const noexcept override { return "функция не поддерживается на данной платформе"; }
    };

    // Некоторая операция, которую можно выполнить на плафторме
    class Operation {
    public:
        virtual std::unique_ptr<Calc::Object> Calculate(RuntimePlatform &platform) {
            throw PlatformNotSupported();
        };

        virtual std::unique_ptr<Calc::Object> Calculate(CPUPlatform& platform) {
            throw PlatformNotSupported();
        }

        virtual ~Operation() =default;
    };
}
#endif //CALC_FUNCTION_H

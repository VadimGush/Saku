#ifndef CALC_FUNCTION_H
#define CALC_FUNCTION_H

#include <iostream>
#include <exception>
#include <memory>

namespace Calc {

    class RuntimePlatform;
    class CPUPlatform;

    // Если операция не поддерживает выполнение на текущей платформе
    struct PlatformNotSupported : public std::exception {};

    // Некоторая операция, которую можно выполнить на плафторме
    class Operation {
    public:
        virtual std::unique_ptr<Result> Calculate(RuntimePlatform &platform) {
            throw PlatformNotSupported();
        };

        virtual std::unique_ptr<Result> Calculate(CPUPlatform& platform) {
            throw PlatformNotSupported();
        }

        virtual ~Operation() =default;
    };
}
#endif //CALC_FUNCTION_H

//
// Created by tsukuto on 18.03.19.
//

#ifndef CALC_FUNCTION_H
#define CALC_FUNCTION_H

#include <iostream>
#include <exception>

namespace Calc {

    class RuntimePlatform;
    class CPUPlatform;

    // Если операция не поддерживает выполнение на текущей платформе
    struct PlatformNotSupported : public std::exception {};

    // Некоторая операция, которую можно выполнить на плафторме
    class Operation {
    public:
        virtual void Calculate(RuntimePlatform &platform, std::ostream &output) {
            throw PlatformNotSupported();
        };

        virtual void Calculate(CPUPlatform& platform, std::ostream& output) {
            throw PlatformNotSupported();
        }

        virtual ~Operation() =default;
    };
}
#endif //CALC_FUNCTION_H

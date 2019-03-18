//
// Created by tsukuto on 18.03.19.
//

#ifndef CALC_FUNCTION_H
#define CALC_FUNCTION_H

#include <iostream>

namespace Calc {

    class RuntimePlatform;
    class CPUPlatform;

    // Выполнение некоторой функции не поддерживается на данной платформе
    struct PlatformNotSupported {};

    // Функция выполняет некоторые вычисления на указанной платформе
    class Function {
    public:
        virtual void Calculate(RuntimePlatform &platform, std::ostream &output) {
            throw PlatformNotSupported();
        };

        virtual void Calculate(CPUPlatform& platform, std::ostream& output) {
            throw PlatformNotSupported();
        }

        virtual ~Function() =default;
    };
}
#endif //CALC_FUNCTION_H

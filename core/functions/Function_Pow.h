//
// Created by tsukuto on 18.03.19.
//

#ifndef CALC_FUNCTION_POW_H
#define CALC_FUNCTION_POW_H


#include "Function.h"

namespace Calc {
    class Function_Pow : public Function {
    public:

        Function_Pow(double base, double power);

        void Calculate(RuntimePlatform& platform, std::ostream& output) override;

    private:
        double base_;
        double power_;
    };
}


#endif //CALC_FUNCTION_POW_H

#ifndef CALC_FUNCTION_POW_H
#define CALC_FUNCTION_POW_H


#include "Operation.h"

namespace Calc {
    class Operation_Pow : public Operation {
    public:

        Operation_Pow(double base, double power);

        std::unique_ptr<Calc::Object> Calculate(RuntimePlatform& platform) override;

    private:
        double base_;
        double power_;
    };
}


#endif //CALC_FUNCTION_POW_H

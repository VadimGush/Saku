#ifndef CALC_FUNCTION_POW_H
#define CALC_FUNCTION_POW_H


#include "Operation.h"

namespace Calc {
    class Operation_Pow : public Operation {
    public:

        void init(std::shared_ptr<Calc::Object> args) override;

        std::unique_ptr<Calc::Object> Calculate(RuntimePlatform &platform) override;

    private:
        double base_;
        double power_;
    };
}


#endif //CALC_FUNCTION_POW_H

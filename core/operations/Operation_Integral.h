//
// Created by tsukuto on 26.03.19.
//

#ifndef SAKU_OPERATION_INTERGRAL_H
#define SAKU_OPERATION_INTERGRAL_H

#include "Operation.h"
#include <functional>
#include <memory>

namespace Calc {
    using function_type = std::function<double(double)>;

    class Operation_Integral : public Operation {
    public:
        Operation_Integral(std::shared_ptr<function_type> function, double a, double b);

        void Calculate(RuntimePlatform&, std::ostream&) override;
    private:
        std::shared_ptr<function_type> function_;
        std::pair<double, double> range_;
        const int n_ = 1000;
    };
}


#endif //SAKU_OPERATION_INTERGRAL_H

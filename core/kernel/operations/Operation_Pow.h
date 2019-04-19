#ifndef CALC_FUNCTION_POW_H
#define CALC_FUNCTION_POW_H


#include "Operation.h"

namespace Calc {
    class Operation_Pow : public Operation {
    public:

        explicit Operation_Pow(const std::shared_ptr<Object>&);

        std::unique_ptr<Calc::Object> Calculate() override;

    private:
        double base_;
        double power_;
    };
}


#endif //CALC_FUNCTION_POW_H

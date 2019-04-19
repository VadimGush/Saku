#ifndef SAKU_OPERATION_INTERGRAL_H
#define SAKU_OPERATION_INTERGRAL_H

#include "Operation.h"
#include <functional>
#include <memory>

namespace Calc {
    using function_type = std::function<double(double)>;

    class Operation_Integral : public Operation {
    public:

        explicit Operation_Integral(const std::shared_ptr<Calc::Object>&);

        std::unique_ptr<Calc::Object> Calculate() override;

    private:
    };
}


#endif //SAKU_OPERATION_INTERGRAL_H

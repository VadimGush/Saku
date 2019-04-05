#ifndef SAKU_OPERATION_INTERGRAL_H
#define SAKU_OPERATION_INTERGRAL_H

#include "Operation.h"
#include <functional>
#include <memory>

namespace Calc {
    using function_type = std::function<double(double)>;

    class Operation_Integral : public Operation {
    public:

        void init(std::shared_ptr<Calc::Object>) override;

        std::unique_ptr<Calc::Object> Calculate(RuntimePlatform &) override;

    private:
    };
}


#endif //SAKU_OPERATION_INTERGRAL_H

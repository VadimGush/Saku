//
// Created by tsukuto on 19.04.19.
//

#ifndef SAKU_OPERATION_SIZE_H
#define SAKU_OPERATION_SIZE_H

#include "Operation.h"

namespace Calc {
    class Operation_Size : public Operation {
    public:
        Operation_Size(const std::shared_ptr<Calc::Object>& arg) {
            size_ = arg->size();
        }

        std::unique_ptr<Calc::Object> Calculate() override {
            return std::make_unique<Calc::NumberObject>(size_);
        }
    private:
        size_t size_;
    };
}

#endif //SAKU_OPERATION_SIZE_H

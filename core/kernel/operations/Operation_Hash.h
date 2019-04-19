//
// Created by tsukuto on 19.04.19.
//

#ifndef SAKU_OPERATION_HASH_H
#define SAKU_OPERATION_HASH_H

#include "Operation.h"

namespace Calc {
    class Operation_Hash : public Operation {
    public:
        explicit Operation_Hash(const std::shared_ptr<Calc::Object>& object) {
            std::ostringstream output;
            output << object->hash();
            hash_ = output.str();
        }

        std::unique_ptr<Calc::Object> Calculate() override {
            return std::make_unique<Calc::StringObject>(hash_);
        }
    private:
        std::string hash_;
    };
}

#endif //SAKU_OPERATION_HASH_H

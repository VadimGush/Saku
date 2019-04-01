#ifndef CALC_CPUPLATFORM_H
#define CALC_CPUPLATFORM_H

#include "Platform.h"
#include <CL/cl2.hpp>

namespace Calc {
    class CPUPlatform : public Platform {
    public:
        CPUPlatform(std::string name, cl::Device device)
        : Platform(std::move(name)), device_(std::move(device)) {}

        void Handle(Operation& operation) override {
            operation.Calculate(*this);
        }

        cl::Device GetDevice() { return device_; }
    private:
        cl::Device device_;
    };
}


#endif //CALC_CPUPLATFORM_H

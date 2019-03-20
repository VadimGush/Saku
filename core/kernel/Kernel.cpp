//
// Created by tsukuto on 18.03.19.
//

#include "Kernel.h"
#include "RuntimePlatform.h"
#include "CPUPlatform.h"
#include <iostream>
using namespace Calc;

Kernel* Kernel::instance_ = nullptr;

Kernel* Kernel::Instance() {
    if (instance_ == nullptr)
        instance_ = new Kernel();
    return instance_;
}

static void init_opencl(std::vector<std::shared_ptr<Platform>>& platforms_) {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Device device;
    for (auto &p : platforms) {
        // Добавляем все CPU, которые поддерживают OpenCL 2.0
        if (p.getInfo<CL_PLATFORM_VERSION>().find("OpenCL 2.") != std::string::npos) {
            std::vector<cl::Device> devices;
            p.getDevices(CL_DEVICE_TYPE_CPU, &devices);
            for (auto& d : devices)
                platforms_.push_back(std::make_shared<Calc::CPUPlatform>("OpenCL 2.0: " + d.getInfo<CL_DEVICE_NAME>(), d));
        }
    }
}

Kernel::Kernel() {
    // Runtime платформа для выполнения вычислений внутри программы
    platforms_.push_back(std::make_shared<RuntimePlatform>());
    // И устанавливаем её в качестве стандартной
    current_platform_ = platforms_[0];
    // Получаем все доступные устройства из OpenCL
    init_opencl(platforms_);
}


#include "Kernel.h"
#include "RuntimePlatform.h"
#include "CPUPlatform.h"
#include "operations/Operation_Integral.h"
#include "operations/Operation_Pow.h"

using namespace Calc;

static void init_opencl(std::vector<std::shared_ptr<Platform>> &platforms_) {
    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    cl::Device device;
    for (auto &p : platforms) {
        // Добавляем все CPU, которые поддерживают OpenCL 2.0
        if (p.getInfo<CL_PLATFORM_VERSION>().find("OpenCL 2.") != std::string::npos) {
            std::vector<cl::Device> devices;
            p.getDevices(CL_DEVICE_TYPE_CPU, &devices);
            for (auto &d : devices)
                platforms_.push_back(
                        std::make_shared<Calc::CPUPlatform>("OpenCL 2.0: " + d.getInfo<CL_DEVICE_NAME>(), d));
        }
    }
}

std::shared_ptr<Kernel> Kernel::instance_ = nullptr;

std::shared_ptr<Kernel> Kernel::Instance() {
    if (instance_ == nullptr)
        instance_ = std::shared_ptr<Kernel>(new Kernel());
    return instance_;
}

std::unique_ptr<Object> Kernel::Calculate(const std::string& function_name, const std::shared_ptr<Calc::Object>& args) {
    using namespace std;
    unique_ptr<Calc::Operation> operation;

    if (function_name == "integral")    operation = make_unique<Calc::Operation_Integral>(args);
    if (function_name == "pow")         operation = make_unique<Calc::Operation_Pow>(args);


    if (operation != nullptr)
        // TODO: Реализовать кеширование
        return current_platform_->Handle(*operation);
    else {
        ostringstream info;
        info << "Функция " << function_name << "() не найдена";
        throw Calc::FunctionNotFound(info.str());
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


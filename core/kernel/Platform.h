#ifndef CALC_PLATFORM_H
#define CALC_PLATFORM_H

#include <memory>
#include <iostream>
#include "operations/Operation.h"

namespace Calc {

    // Платформа описывает устройство, на котором возможно провести вычисления
    // За инициализацию платформ отвечает Kernel (ядро) и оно же выбирает платформу по умолчанию.
    class Platform {
    public:
        // Запуск функции (операции) на платформе
        virtual void Handle(Operation &) = 0;

        // Наименование платформы
        const std::string &GetName() const { return name_; }

    protected:
        explicit Platform(std::string name) : name_(std::move(name)) {}

        std::string name_;
    };
}

#endif //CALC_PLATFORM_H



//
// Created by tsukuto on 18.03.19.
//

#ifndef CALC_PLATFORM_H
#define CALC_PLATFORM_H

#include <memory>
#include <iostream>
#include "../functions/Function.h"

namespace Calc {

    // Платформа описывает любое устройство (девайс), на котором возможно проводить
    // вычисления
    class Platform {
    public:
        // Запуск функции (операции) на платформе
        virtual void Handle(Function &function, std::ostream &output) =0;

        // Наименование платформы
        const std::string& GetName() const { return name_; }

    protected:
        Platform(std::string name) : name_(std::move(name)) {}

        std::string name_;
    };
}

#endif //CALC_PLATFORM_H



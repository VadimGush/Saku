#ifndef CALC_FUNCTION_H
#define CALC_FUNCTION_H

#include <iostream>
#include <exception>
#include <memory>
#include <sstream>
#include "../objects/Object.h"

namespace Calc {

    class RuntimePlatform;

    class CPUPlatform;

    // Если операция не поддерживает выполнение на текущей платформе
    struct PlatformNotSupported : public std::exception {
        const char *what() const noexcept override { return "функция не поддерживается на данной платформе"; }
    };

    struct InvalidArguments : public std::exception {

        InvalidArguments(const std::string& function_name, int expected_args) {
            std::ostringstream information;
            information << "неверное количество аргментов в функции " << function_name << "(), ";
            information << "ожидается " << expected_args << " арг.";
            message_ = information.str();
        }

        InvalidArguments(const std::string& function_name, ObjectType passed_type, ObjectType expected_type) {
            std::ostringstream information;
            information << "в функцию " << function_name << "() передан аргумент типа " << passed_type;
            information << ", ожидается тип " << expected_type;
            message_ = information.str();
        }

        const char *what() const noexcept override { return message_.c_str(); }

    private:
        std::string message_;
    };

    // Некоторая операция, которую можно выполнить на плафторме
    class Operation {
    public:

        virtual std::unique_ptr<Calc::Object> Calculate(RuntimePlatform &platform) {
            throw PlatformNotSupported();
        };

        virtual std::unique_ptr<Calc::Object> Calculate(CPUPlatform &platform) {
            throw PlatformNotSupported();
        }

        virtual ~Operation() = default;

    };
}
#endif //CALC_FUNCTION_H

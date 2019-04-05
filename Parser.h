#ifndef SAKU_PARSER_H
#define SAKU_PARSER_H

#include <iostream>
#include "core/kernel/objects/Object.h"
#include <memory>
#include <exception>
#include <stdexcept>

namespace Calc {

    class ParserException : public std::exception {
    public:
        explicit ParserException(std::string message) : what_(std::move(message)) {}

        const char* what() const noexcept override { return what_.c_str(); }
    private:
        std::string what_;
    };

    // Удаляет пробелы везде, но не внутри кавычек
    void remove_spaces(std::string &) noexcept;

    // Является ли символ частью допустимого имени переменной или функции
    bool isvar(char) noexcept;

    // Проверяет, являются ли символы выражения допустимыми
    void is_valid(const std::string& input);

    // Парсим выражение
    std::shared_ptr <Calc::Object> parse(std::string::iterator begin, std::string::iterator end);

}


#endif //SAKU_PARSER_H

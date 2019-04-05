#ifndef CALC_COMMAND_H
#define CALC_COMMAND_H

#include <iostream>

namespace Calc {

    // Command - оболочка для команды.
    // Команда не выполняет каких-либо вычислений, а используется только для вывода полезной информации.
    // Каждая команда содержит описание, которое выводится при вводе help в терминале.
    // Все команды регистрируются в классе CommandManager
    class Command {
    public:
        Command();

        explicit Command(std::string description);

        Command(const Command &) = delete;

        virtual void Run(std::ostream &output) = 0;

        const std::string &GetDescription() const;

        virtual ~Command() = default;

    private:
        const std::string description_;
    };

}


#endif //CALC_COMMAND_H

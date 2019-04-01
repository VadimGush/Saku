#ifndef CALC_COMMAND_H
#define CALC_COMMAND_H

#include <iostream>

namespace Calc {
    class Command {
    public:
        Command();
        explicit Command(std::string description);

        Command(const Command&) =delete;

        virtual void Run(std::ostream& output) = 0;
        const std::string& GetDescription() const;

        virtual ~Command() = default;
    private:
        const std::string description_;
    };
}


#endif //CALC_COMMAND_H

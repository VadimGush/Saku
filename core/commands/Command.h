//
// Created by tsukuto on 15.03.19.
//

#ifndef CALC_COMMAND_H
#define CALC_COMMAND_H

#include <iostream>

namespace Calc {
    class Command {
    public:
        Command();
        explicit Command(std::string description);

        Command(const Command&) =delete;

        virtual void Handle(std::istream &input, std::ostream &output) = 0;
        const std::string& GetDescription() const;

        virtual ~Command() = default;
    private:
        const std::string description_;
    };
}


#endif //CALC_COMMAND_H

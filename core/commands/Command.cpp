//
// Created by tsukuto on 15.03.19.
//

#include "Command.h"
using namespace Calc;

Command::Command() : description_("<no discription>") {}

Command::Command(std::string description) : description_(std::move(description)) {}

const std::string& Command::GetDescription() const {
    return description_;
}



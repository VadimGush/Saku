#include "Command.h"
using namespace Calc;

Command::Command() : description_("<no description>") {}

Command::Command(std::string description) : description_(std::move(description)) {}

const std::string& Command::GetDescription() const {
    return description_;
}



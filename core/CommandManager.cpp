//
// Created by tsukuto on 15.03.19.
//

#include "CommandManager.h"

using namespace Calc;

CommandManager* CommandManager::instance_ = nullptr;

CommandManager* CommandManager::Instance() {
    if (instance_ == nullptr)
        instance_ = new CommandManager{};
    return instance_;
}

std::shared_ptr<Command> CommandManager::GetCommand(const std::string& command) const {
    return commands_.at(command);
}

const std::map<std::string, std::shared_ptr<Command>>& CommandManager::GetCommandMap() const {
    return commands_;
}
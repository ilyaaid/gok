#pragma once

#include <string>
#include <vector>
#include <memory>

#include "instruction.hpp"
#include "function.hpp"

class Function;

class BasicBlock {
    std::string name;
    std::vector<std::shared_ptr<Instruction>> Instructions;
    Function* func;

public:
    BasicBlock(const std::string& name, Function* func): name(name), func(func) {};

    static BasicBlock* Create(const std::string& name, Function* func);
};

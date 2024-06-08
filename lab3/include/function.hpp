#pragma once

#include "basic_block.hpp"
#include "module.hpp"

class Module;
class BasicBlock;

class Function {
    std::string name;
    std::vector<std::shared_ptr<BasicBlock>> blocks;
    Module* module;

public:
    Function(const std::string name, Module* module): name(name), module(module) {};

    static Function* Create(const std::string name, Module* module);

    void addBlock(std::shared_ptr<BasicBlock> block) {
        blocks.push_back(block);
    }
};

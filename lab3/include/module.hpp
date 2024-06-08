#pragma once

#include <memory>

#include "function.hpp"

class Function;

class Module {
    std::vector<std::shared_ptr<Function>> funcs;
    
    public:
    void addFunc(std::shared_ptr<Function> func) {
        funcs.push_back(func);
    }
};

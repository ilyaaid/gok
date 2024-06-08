#include "function.hpp"

Function* Function::Create(const std::string name, Module* module) {
    auto func = std::make_shared<Function>(name, module);
    module->addFunc(func);
    return func.get();
}

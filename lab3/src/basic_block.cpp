#include "basic_block.hpp"

BasicBlock* BasicBlock::Create(const std::string& name, Function* func) {
    auto block = std::make_shared<BasicBlock>(name, func);
    func->addBlock(block);
    return block.get();
}

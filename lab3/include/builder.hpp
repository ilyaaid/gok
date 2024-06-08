#pragma once

#include "basic_block.hpp"

class Builder {
    BasicBlock* active_block = nullptr;

public:
    void SetInsertPoint(BasicBlock* new_block);

    
};

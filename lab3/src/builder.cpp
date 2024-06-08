#include "builder.hpp"


void Builder::SetInsertPoint(BasicBlock* new_block)
{
    active_block = new_block;
}



#include "ast_tree.hpp"

#include "function.hpp"
#include "basic_block.hpp"

#include <iostream>

Function* FunctionAST::codegen(LLVMData& data)
{
    if (type == "int") {
        auto func = Function::Create(name, &data.module);
        auto innerblock = BasicBlock::Create("entry", func);
        data.builder.SetInsertPoint(innerblock);

        // auto functionType = FunctionType::get(Type::getInt32Ty(*(data.context)), false);
        // auto func = Function::Create(functionType, Function::ExternalLinkage, name, *(data.module));
        // auto innerblock = BasicBlock::Create(*(data.context), "entry", func);
        // data.builder->SetInsertPoint(innerblock);

        for (auto& st : statements) {
            st->codegen(data);
        }
        return func;
    }
    throw std::runtime_error("unknown type of function");
}


void ReturnSt::codegen(LLVMData& data)
{
    data.builder.CreateRet(expr->codegen(data));
    // data.builder->CreateRet(expr->codegen(data));
}


// void AssignSt::codegen(LLVMData& data)
// {
//     if (type == "int") {
//         // аллоцировал новую переменную
//         AllocaInst* alloc_v = data.builder->CreateAlloca(data.builder->getInt32Ty(), 
//         nullptr, var);
//         // добавил в мапу новую переменную
//         data.named_vars[var] = alloc_v;
//     }
// }

// void ReAssignSt::codegen(LLVMData& data)
// {
//     AllocaInst* alloc_v = data.named_vars[var];
//     if (!alloc_v) {
//         throw std::runtime_error("Unknown variable: " + var);
//     }

//     Value* rhs_v = value->codegen(data);
//     data.builder->CreateStore(rhs_v, alloc_v);
// }


// void IfSt::codegen(LLVMData& data)
// {
//     Value* cmp = cond->codegen(data);

//     Function* func = data.builder->GetInsertBlock()->getParent();

//     BasicBlock* less_block = llvm::BasicBlock::Create(*(data.context), "less", func);
//     BasicBlock* greater_block = llvm::BasicBlock::Create(*(data.context), "greater", func);
//     BasicBlock* mergeBlock = llvm::BasicBlock::Create(*(data.context), "merge", func);

//     data.builder->CreateCondBr(cmp, less_block, greater_block);

//     data.builder->SetInsertPoint(less_block);
//     for (size_t i = 0; i < then_sts.size(); ++i) {
//         then_sts[i]->codegen(data);
//     }
//     data.builder->CreateBr(mergeBlock);

//     data.builder->SetInsertPoint(greater_block);
//     for (size_t i = 0; i < else_sts.size(); ++i) {
//         else_sts[i]->codegen(data);
//     }
//     data.builder->CreateBr(mergeBlock);

//     data.builder->SetInsertPoint(mergeBlock);
// }

// void WhileSt::codegen(LLVMData& data)
// {
//     Function* func = data.builder->GetInsertBlock()->getParent();
//     BasicBlock* whileHeader = BasicBlock::Create(*(data.context), "whileHeader", func);
//     BasicBlock* whileBody = BasicBlock::Create(*(data.context), "whileBody", func);
//     BasicBlock* whileEnd = BasicBlock::Create(*(data.context), "whileEnd", func);

//     data.builder->CreateBr(whileHeader);

//     data.builder->SetInsertPoint(whileHeader);

//     llvm::Value* conditionValue = cond->codegen(data);
//     data.builder->CreateCondBr(conditionValue, whileBody, whileEnd);

//     data.builder->SetInsertPoint(whileBody);
//     for (size_t i = 0; i < while_sts.size(); ++i) {
//         while_sts[i]->codegen(data);
//     }
//     data.builder->CreateBr(whileHeader);

//     data.builder->SetInsertPoint(whileEnd);
// }


// /*==========================================================*/
// /*========================== Exprs =========================*/


// Value* NumberExprAST::codegen(LLVMData& data)
// {
//     return ConstantInt::get(*(data.context), APInt(32, val));
// }

// Value* VariableExprAST::codegen(LLVMData& data)
// {
//     AllocaInst* v = data.named_vars[name];
//     if (!v) {
//         throw std::runtime_error("Unknown variable name: " + name);
//     }
//     return data.builder->CreateLoad(v->getAllocatedType(), v, name);
// }


// Value* BinaryExprAST::codegen(LLVMData& data)
// {
//     if (op == "+") {
//         return data.builder->CreateAdd(lhs->codegen(data), rhs->codegen(data));
//     }
//     else if (op == "-") {
//         return data.builder->CreateSub(lhs->codegen(data), rhs->codegen(data));
//     }
//     else if (op == "*") {
//         return data.builder->CreateMul(lhs->codegen(data), rhs->codegen(data));
//     }
//     else if (op == "/") {
//         return data.builder->CreateSDiv(lhs->codegen(data), rhs->codegen(data));
//     }
//     else if (op == "<") {
//         return data.builder->CreateICmpSLT(lhs->codegen(data), rhs->codegen(data));
//     }
//     else if (op == ">") {
//         return data.builder->CreateICmpSGT(lhs->codegen(data), rhs->codegen(data));
//     }
//     else {
//         throw std::runtime_error("unknown bin operation");
//     }
//     return nullptr;
// }

void AssignSt::codegen(LLVMData& data)
{
}

void ReAssignSt::codegen(LLVMData& data)
{
}

void IfSt::codegen(LLVMData& data)
{
}

void WhileSt::codegen(LLVMData& data)
{
}

void ReturnSt::codegen(LLVMData& data)
{
}

Instruction* NumberExprAST::codegen(LLVMData& data)
{
    return nullptr;
}

Instruction* VariableExprAST::codegen(LLVMData& data)
{
    return nullptr;
}

Instruction* BinaryExprAST::codegen(LLVMData& data)
{
    return nullptr;
}

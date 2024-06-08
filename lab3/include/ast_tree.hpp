#pragma once

// #include <llvm/IR/Type.h>
// #include <llvm/IR/BasicBlock.h>
// #include <llvm/IR/Function.h>

#include "llvm_data.hpp"

// using namespace llvm;

class ExprAST;
class StatementAST;

class FunctionAST {
    std::string type;
    std::string name;
    std::vector<std::unique_ptr<StatementAST>> statements;

public:
    FunctionAST(const std::string& type, const std::string& name,
        std::vector<std::unique_ptr<StatementAST>> statements)
        : type(type), name(name), statements(std::move(statements)) {}

    Function* codegen(LLVMData& data);
};

/*=============================================================================*/
/*================================ Statements =================================*/

class StatementAST {
public:
    virtual ~StatementAST() = default;
    virtual void codegen(LLVMData& data) = 0;
};

class AssignSt : public StatementAST {
    std::string type;
    std::string var;

public:
    AssignSt(const std::string& type, std::string var):
        var(var), type(type) {}

    void codegen(LLVMData& data) override;
};

class ReAssignSt : public StatementAST {
    std::string var;
    std::unique_ptr<ExprAST> value;

public:
    ReAssignSt(std::string var, std::unique_ptr<ExprAST> value):
        var(var), value(std::move(value)) {}

    void codegen(LLVMData& data) override;
};

class IfSt : public StatementAST {
    std::unique_ptr<ExprAST> cond;
    std::vector<std::unique_ptr<StatementAST>> then_sts;
    std::vector<std::unique_ptr<StatementAST>> else_sts;

public:
    IfSt(std::unique_ptr<ExprAST> cond,
        std::vector<std::unique_ptr<StatementAST>> then_sts,
        std::vector<std::unique_ptr<StatementAST>> else_sts):
        cond(std::move(cond)), then_sts(std::move(then_sts)), else_sts(std::move(else_sts)) {}

    void codegen(LLVMData& data) override;
};

class WhileSt : public StatementAST {
    std::unique_ptr<ExprAST> cond;
    std::vector<std::unique_ptr<StatementAST>> while_sts;

public:
    WhileSt(std::unique_ptr<ExprAST> cond,
        std::vector<std::unique_ptr<StatementAST>> while_sts):
        cond(std::move(cond)), while_sts(std::move(while_sts)) {}

    void codegen(LLVMData& data) override;
};

class ReturnSt : public StatementAST {
    std::unique_ptr<ExprAST> expr;
public:
    ReturnSt(std::unique_ptr<ExprAST> expr): expr(std::move(expr)) {}

    void codegen(LLVMData& data) override;
};



/*========================================================================*/
/*================================ Exprs =================================*/

class ExprAST {
public:
    virtual ~ExprAST() = default;
    virtual Value* codegen(LLVMData& data) = 0;
};

class NumberExprAST : public ExprAST {
    int val;

public:
    NumberExprAST(int val): val(val) {}

    Value* codegen(LLVMData& data) override;
};


class VariableExprAST : public ExprAST {
    std::string name;

public:
    VariableExprAST(const std::string& name): name(name) {}

    Value* codegen(LLVMData& data) override;
};

class BinaryExprAST : public ExprAST {
    std::string op;
    std::unique_ptr<ExprAST> lhs, rhs;

public:
    BinaryExprAST(std::string op, std::unique_ptr<ExprAST> LHS,
        std::unique_ptr<ExprAST> rhs)
        : op(op), lhs(std::move(LHS)), rhs(std::move(rhs)) {}

    Value* codegen(LLVMData& data) override;
};



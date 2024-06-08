#pragma once

// #include <llvm/IR/Verifier.h>
// #include <llvm/IR/Type.h>
// #include <llvm/IR/Module.h>
// #include <llvm/IR/IRBuilder.h>
// #include <llvm/Support/raw_ostream.h>
// #include <llvm/IR/Dominators.h>
// #include <llvm/IR/CFG.h>
// #include "llvm/Analysis/DominanceFrontier.h"

#include <map>
#include <memory>

#include "module.hpp"
#include "basic_block.hpp"
#include "builder.hpp"

// using namespace llvm;

struct LLVMData {
    // std::unique_ptr<LLVMContext> context;
    // std::unique_ptr<Module> module;
    // std::unique_ptr<IRBuilder<>> builder;
    // std::map<std::string, AllocaInst*> named_vars;
    Module module;
    Builder builder;

    LLVMData() {
        // context = std::make_unique<LLVMContext>();
        // module = std::make_unique<Module>("my_module", *context);
        // builder = std::make_unique<IRBuilder<>>(*context);
    }

    // void verify() const {
    //     verifyModule(*module, &errs());
    // }

    // void printLLVMCode() const {
    //     std::error_code error_code;
    //     raw_fd_ostream output_file("/home/ilya/projects/bmstu/gok/lab2/src/__llvm.txt", error_code);
    //     if (error_code) {
    //         errs() << "Error opening file: " << error_code.message() << "\n";
    //         return;
    //     }

    //     module->print(output_file, nullptr);

    //     // module->print(errs(), nullptr);
    // }

    // void findStoreInstructions() {
    //     llvm::Instruction* inst;
    //     for (llvm::Function& function : *module) {
    //         for (llvm::BasicBlock& block : function) {
    //             for (llvm::Instruction& instruction : block) {
    //                 if (llvm::isa<llvm::StoreInst>(&instruction)) {
    //                     // llvm::outs() << "Block: " << instruction.getParent()->getName() << "\n";
    //                     // llvm::outs() << "Found store instruction: " << instruction << "\n";
    //                     inst = &instruction;
    //                 }
    //             }
    //         }
    //     }
    // }

    // void printCFG() {
    //     for (llvm::Function& function : *module) {
    //         llvm::outs() << "Control Flow Graph for function: " << function.getName() << "\n";

    //         for (llvm::BasicBlock& block : function) {
    //             llvm::outs() << "  Basic Block: " << block.getName() << "\n";

    //             for (llvm::succ_iterator it = succ_begin(&block), e = succ_end(&block); it != e; ++it) {
    //                 llvm::BasicBlock* successorBlock = *it;
    //                 llvm::outs() << "    Successor: " << successorBlock->getName() << "\n";
    //             }
    //         }

    //         llvm::outs() << "\n";
    //     }
    // }

    
};

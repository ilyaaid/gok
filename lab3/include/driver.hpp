#pragma once

#include <memory>

#include "scanner.hpp"
#include "ast_tree.hpp"

class Driver
{
public:
    void common(ps::Parser::value_type* lval,
    const std::string& yytext);

public:
    std::string cur_text;
    bool continued = false;

    std::unique_ptr<FunctionAST> rootAST;

    int enclosure = 0;
};

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Parser/Parser.hpp"
#include "Lexer/Lexer.hpp"
#include "Parser/Expressions.hpp"
#include "IRGeneration/IRGenerator.hpp"



int main(int argc, const char* argv[]) {
    const char* file_name = "program.txt";
    // if (argc > 1)
    // {
    FILE* fp = freopen(file_name, "r", stdin);
    if (fp == NULL)
    {
        perror(file_name);
        exit(1);
    }
    // } else {
    //     printf("type file in arg\n");
    //     exit(1);
    // }



    std::vector<AbstractExpression*> expressions = Parser(new Lexer()).Parse();


    IRGenerator irGenerator = IRGenerator();
    for (std::vector<AbstractExpression*>::iterator it = expressions.begin(); it != expressions.end(); ++it)
        irGenerator.GenerateIR((*it));


    irGenerator.CommitBuildingAndDump(false);
    printf("---\n");
    irGenerator.PrintDot();


    return 0;
}

#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <fstream>

#include "scanner.hpp"
#include "driver.hpp"

#include "llvm_data.hpp"

using namespace std;

int main() {
    const string input_file = "/home/ilya/projects/bmstu/gok/lab2/src/__input.cpp";
    ifstream in(input_file);
    Scanner scanner(&in, &cout);

    Driver driver;
    ps::Parser parser(scanner, driver);
    parser.parse();

    LLVMData data;
    driver.rootAST->codegen(data);

    data.verify();
    data.printLLVMCode();

    // data.findStoreInstructions();

    // data.printCFG();
    cout << endl;
    return 0;
}

#ifndef SCANNER
#define SCANNER
#include <string>
#include <iostream>
#include "Token.h"
#include "StateMachine.h"
#include <fstream>      // std::ifstream


class ScannerClass{

public:
    ScannerClass(const std::string& input);
    ~ScannerClass();
    TokenClass GetNextToken();
    int GetLineNumber();
    TokenClass PeekNextToken();
    void tellg(int mLineNumber);
    void seekg(int mLineNumber);
private:
    std::ifstream mFin;
    int mLineNumber;
};

#endif //SCANNER
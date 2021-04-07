#include "Scanner.h"
#include "Token.h"
#include "Debug.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ScannerClass::ScannerClass(const std::string& inputFileName){
    MSG("Initializing ScannerClass object");
    mFin.open(inputFileName.c_str(), std::ios::binary);
    if (mFin.is_open()){
        mLineNumber = 1;
        cout << "File successfully opened" << endl;
    } else{
        printf ("Error opening file");
        exit (EXIT_FAILURE);
    }
}
ScannerClass::~ScannerClass(){
    mFin.close();
}

TokenClass ScannerClass::GetNextToken(){
    MachineState currentState;
    StateMachineClass stateMachine;
    TokenType correspondingTokenType;
    char c;
    string lexeme;
    do{
        c = mFin.get();
        lexeme += c;
        currentState = stateMachine.UpdateState(c, correspondingTokenType);
        
        if (currentState == START_STATE){
            lexeme = "";
        };
        if(c == '\n'){
            mLineNumber += 1;
        }
    
    }while (currentState != CANTMOVE_STATE);
        mFin.unget();
        lexeme.pop_back();

        // if(c=='\n'){
        //     mLineNumber -= 1;
        // }

    if(correspondingTokenType == BAD_TOKEN){
        printf("Bad token type on GetNextToken()");
        exit(EXIT_FAILURE);
    }

    TokenClass tc (correspondingTokenType, lexeme);
    tc.CheckReserved();
    return tc;
}

int ScannerClass::GetLineNumber(){
    return mLineNumber;
}

TokenClass ScannerClass::PeekNextToken(){
    std::streampos pos = this->mFin.tellg();
    int line = this->mLineNumber;

    TokenClass tc = GetNextToken();
    if(!this->mFin){ // if we triggered EOF, then seekg doesn't work,
        this->mFin.clear(); // unless we first clear()
    }
    this->mFin.seekg(pos);
    this->mLineNumber = line;

    return tc;
}
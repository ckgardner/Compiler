#include "Token.h"
#include <iostream>
#include <iomanip>

TokenClass::TokenClass(TokenType type, const std::string & lexeme){
    mType = type;
    mLexeme = lexeme;
}

void TokenClass::CheckReserved(){
    if(mLexeme == "void"){
        mType = VOID_TOKEN;
    }
    if(mLexeme == "main"){
        mType = MAIN_TOKEN;
    }
    if(mLexeme == "int"){
        mType = INT_TOKEN;
    }
    if(mLexeme == "cout"){
        mType = COUT_TOKEN;
    }
    if(mLexeme == "if"){
        mType = IF_TOKEN;
    }
    if(mLexeme == "else"){
        mType = ELSE_TOKEN;
    }
    if(mLexeme == "while"){
        mType = WHILE_TOKEN;
    }
    if(mLexeme == "repeat"){
        mType = REPEAT_TOKEN;
    }
}

std::ostream & operator<<(std::ostream & out, const TokenClass & tc){
    out.setf(std::ios::left);
    out << "Type: " << std::setw(15) << tc.GetTokenTypeName() <<
            "Lexeme: " << std::setw(15) << tc.GetLexeme();
    return out;
}
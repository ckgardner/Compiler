#ifndef PARSER
#define PARSER
#include <string>
#include <iostream>
#include "Symbol.h"
#include "Scanner.h"
#include "Node.h"
using namespace std;

class ParserClass{
public:
    ParserClass(ScannerClass* sc, SymbolTableClass* stc);
    StartNode * Start();
private:
    TokenClass Match(TokenType expectedType);
    ProgramNode * Program();
    BlockNode * Block();
    IfStatementNode * IfStatement();
    WhileStatementNode * WhileStatement();
    RepeatStatementNode * RepeatStatement();
    DeclarationStatementNode * DeclarationStatement();
    AssignmentStatementNode * AssignmentStatement();
    CoutStatementNode * CoutStatement();
    ExpressionNode * Expression();
    ExpressionNode * Relational();
    StatementGroupNode * StatementGroup();
    StatementNode * Statement();
    ExpressionNode * PlusMinus();
    ExpressionNode * TimesDivide();
    ExpressionNode * Exponent();
    ExpressionNode * Factor();
    IdentifierNode * Identifier();
    IntegerNode * Integer();
    ExpressionNode * BitwiseAndExpression();
    ExpressionNode * AndExpression();
    ExpressionNode * OrExpression();

    ScannerClass * mScanner;
    SymbolTableClass * mSymbolTable;
};


#endif //PARSER
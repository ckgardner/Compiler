#include "Parser.h"
#include "Debug.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
using namespace std;

ParserClass::ParserClass(ScannerClass* sc, SymbolTableClass* stc){
    this->mSymbolTable = stc;
    this->mScanner = sc;
}

StartNode * ParserClass::Start(){
    ProgramNode *pn = Program();
    Match(ENDFILE_TOKEN);
    StartNode * sn = new StartNode(pn);
    return sn;
}


TokenClass ParserClass::Match(TokenType expectedType){
    TokenClass currentToken = this->mScanner->GetNextToken();
    if(currentToken.GetTokenType() != expectedType){
        cerr << "Error in ParserClass::Match. " << endl;
        cerr << "Expected token type " <<
        TokenClass:: GetTokenTypeName(expectedType) <<
        ", but got type " << currentToken.GetTokenTypeName()
        << endl;
        exit(1);
    }
    cout << ("\tSuccessfully matched Token Type: ") << 
    currentToken. GetTokenTypeName() << ". Lexeme: \"" <<
    currentToken.GetLexeme() << "\""  << endl;
    return currentToken; // the one we just processed
}

ProgramNode * ParserClass::Program(){
    Match(VOID_TOKEN);
    Match(MAIN_TOKEN);
    Match(LPAREN_TOKEN);
    Match(RPAREN_TOKEN);
    BlockNode* bn = Block();
    return new ProgramNode(bn);
}

BlockNode * ParserClass::Block() {
    Match(LCURLY_TOKEN);
    StatementGroupNode* sgn = StatementGroup();
    Match(RCURLY_TOKEN);
    return new BlockNode(sgn);
}

StatementGroupNode * ParserClass::StatementGroup(){
    StatementGroupNode * sgn = new StatementGroupNode;
    StatementNode * sn;
    do {
        sn = this->Statement();
        if (sn != NULL) {
            sgn->AddStatement(sn);
        }
    } while (sn != NULL);
    return sgn;
}

StatementNode * ParserClass::Statement(){
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == INT_TOKEN){
        return DeclarationStatement();
    }
    else if(tt == IDENTIFIER_TOKEN){
        return AssignmentStatement();
    }
    else if(tt == COUT_TOKEN){
        return CoutStatement();
    }else if(tt == IF_TOKEN){
        return IfStatement();
    }else if(tt == WHILE_TOKEN){
        return WhileStatement();
    }else if(tt == REPEAT_TOKEN){
        return RepeatStatement();
    }else{
        return NULL;
    }
}

IfStatementNode * ParserClass::IfStatement(){
    Match(IF_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode* en = Expression();
    Match(RPAREN_TOKEN);
    BlockNode* bn = Block();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == ELSE_TOKEN){
        Match(ELSE_TOKEN);
        BlockNode* bn2 = Block();
        return new IfStatementNode(en, bn, bn2);
    }
    return new IfStatementNode(en, bn, NULL);
}

WhileStatementNode * ParserClass::WhileStatement(){
    Match(WHILE_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode* en = Expression();
    Match(RPAREN_TOKEN);
    BlockNode* bn = Block();
    return new WhileStatementNode(en, bn);
}

RepeatStatementNode * ParserClass::RepeatStatement(){
    Match(REPEAT_TOKEN);
    Match(LPAREN_TOKEN);
    ExpressionNode* en = Expression();
    Match(RPAREN_TOKEN);
    BlockNode* bn = Block();
    return new RepeatStatementNode(en, bn);
}

DeclarationStatementNode * ParserClass::DeclarationStatement(){
    Match(INT_TOKEN);
    IdentifierNode * in = Identifier();
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == SEMICOLON_TOKEN){
        Match(SEMICOLON_TOKEN);
        return new DeclarationStatementNode(in, NULL);
    }
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode * en = Expression();
    Match(SEMICOLON_TOKEN);
    return new DeclarationStatementNode(in, en);
}

AssignmentStatementNode * ParserClass::AssignmentStatement(){
    IdentifierNode * in = Identifier();
    Match(ASSIGNMENT_TOKEN);
    ExpressionNode * en = Expression();
    Match(SEMICOLON_TOKEN);
    AssignmentStatementNode * asn = new AssignmentStatementNode(in, en);
    return asn;
}
CoutStatementNode * ParserClass::CoutStatement(){
    Match(COUT_TOKEN);
    Match(INSERTION_TOKEN);
    ExpressionNode * en = Expression();
    Match(SEMICOLON_TOKEN);
    CoutStatementNode * csn = new CoutStatementNode(en);
    return csn;
}

ExpressionNode * ParserClass::Expression(){
    // cout << "Calling Expression()" << endl;
    return OrExpression();
}

ExpressionNode * ParserClass::OrExpression(){
    ExpressionNode * current = AndExpression();

    while(true){
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == OR_TOKEN){
            Match(tt);
            current = new OrNode(current, AndExpression());
        }
        return current;
    }
}

ExpressionNode * ParserClass::AndExpression(){
    ExpressionNode * current = BitwiseAndExpression();

    while (true){
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == AND_TOKEN){
            Match(tt);
            current = new AndNode(current, BitwiseAndExpression());
        }
        return current;
    }
}

ExpressionNode * ParserClass::Relational(){
    // cout << "Calling Relational()" << endl;
    ExpressionNode * current = PlusMinus();
    // Handle the optional tail:
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == LESS_TOKEN){
        Match(tt);
        current = new LessNode(current, PlusMinus());
    }
    else if(tt == LESSEQUAL_TOKEN){
        Match(tt);
        current = new LessEqualNode(current, PlusMinus());
    }
    else if(tt == GREATER_TOKEN){
        Match(tt);
        current = new GreaterNode(current, PlusMinus());
    }
    else if(tt == GREATEREQUAL_TOKEN){
        Match(tt);
        current = new GreaterEqualNode(current, PlusMinus());
    }
    else if(tt == EQUAL_TOKEN){
        Match(tt);
        current = new EqualNode(current, PlusMinus());
    }
    else if(tt == NOTEQUAL_TOKEN){
        Match(tt);
        current = new NotEqualNode(current, PlusMinus());
    }
    return current;
}

ExpressionNode * ParserClass::PlusMinus(){
    ExpressionNode * current = TimesDivide();
    while(true){
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == PLUS_TOKEN){
            Match(tt);
            current = new PlusNode(current, TimesDivide());
        }
        else if(tt == MINUS_TOKEN){
            Match(tt);
            current = new MinusNode(current, TimesDivide());
        }
        return current;
    }
}

ExpressionNode * ParserClass::TimesDivide(){
    // MSG("Calling TimesDivide()");
    ExpressionNode * current = Exponent();
    while(true){
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == TIMES_TOKEN){
            Match(tt);
            current = new TimesNode(current, Exponent());
        }
        else if(tt == DIVIDE_TOKEN){
            Match(tt);
            current = new DivideNode(current, Exponent());
        }
        return current;
    }
}

ExpressionNode * ParserClass::Exponent(){
    ExpressionNode * current = Factor();
    while(true){
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == EXPONENT_TOKEN){
            Match(tt);
            current = new ExponentNode(current, Factor());
        }
        return current;
    }
}

ExpressionNode * ParserClass::Factor(){
    ExpressionNode * en; 
    TokenType tt = mScanner->PeekNextToken().GetTokenType();
    if(tt == IDENTIFIER_TOKEN){
        en = Identifier();
    }
    else if(tt == INTEGER_TOKEN){
        en = Integer();
    }
    else if(tt == LPAREN_TOKEN){
        Match(tt);
        en = Expression();
        Match(RPAREN_TOKEN);
    }else{
        printf ("When peeking in ParserClass::Factor, token not recognized.");
        exit (EXIT_FAILURE);
    }
    return en;
}

ExpressionNode * ParserClass::BitwiseAndExpression(){
    ExpressionNode * current = Relational();

    while (true){
        TokenType tt = mScanner->PeekNextToken().GetTokenType();
        if(tt == BITWISE_AND_TOKEN){
            Match(tt);
            current = new BitwiseAndNode(current, Relational());
        }
        return current;
    }
}

IdentifierNode * ParserClass::Identifier(){
    TokenClass t = Match(IDENTIFIER_TOKEN);
    return new IdentifierNode(t.GetLexeme(), this->mSymbolTable);
}

IntegerNode * ParserClass::Integer(){
    TokenClass t = Match(INTEGER_TOKEN);
    int it = atoi(t.GetLexeme().c_str());
    return new IntegerNode(it);
}
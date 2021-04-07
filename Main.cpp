#include "Token.h"
#include "Scanner.h"
#include "Node.h"
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void testScanner(){
    cout << endl;;
    cout << "TESTING THE SCANNER" << endl;
    ScannerClass scanner("inputFile.txt");
    TokenClass token(VOID_TOKEN,"");
    while (token.GetTokenType() != ENDFILE_TOKEN) {
        token = scanner.GetNextToken();
        cout << "line #: " << scanner.GetLineNumber() << " | token type: " << token.GetTokenTypeName() << " | lexeme: " << token.GetLexeme() << endl;
    }

    TokenType tt = VOID_TOKEN;
    string lexeme = "void";
    TokenClass tok1(tt, lexeme);
    cout << tok1 << endl;
    cout << endl;
}

void testNodes() {
    cout << endl;
    cout << "TESTING THE NODES" << endl;
    StartNode* start = new StartNode(new ProgramNode(new BlockNode(new StatementGroupNode())));
    cout << "deleting start node..." << endl;
    delete start;

    PlusNode* plus = new PlusNode(new IntegerNode(40), new IntegerNode(50));
    cout << "Sum = " << plus->Evaluate() << endl;
    cout << "deleting plusNode..." << endl;
    delete plus;

    LessEqualNode* lte = new LessEqualNode(new IntegerNode(40), new IntegerNode(50));
    cout << "Evaluation = " << lte->Evaluate() << endl;
    cout << "deleting lessEqualNode" << endl;
    delete lte;
    cout << endl;
}

void testParser(std::string fileName) {
    ScannerClass* scanner = new ScannerClass(fileName);
    SymbolTableClass* table = new SymbolTableClass();
    ParserClass* parser = new ParserClass(scanner, table);
    parser->Start();
}

void testInterpreter(std::string fileName){
    ScannerClass* scanner = new ScannerClass(fileName);
    SymbolTableClass* table = new SymbolTableClass();
    ParserClass* parser = new ParserClass(scanner, table);
    StartNode* root = parser->Start();
    root->Interpret();
}

int main(){
    testInterpreter("inputFile.txt");
    // testScanner();
    // testNodes();
    // testParser("inputFile.txt");
    return 0;
}
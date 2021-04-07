#ifndef NODE
#define NODE
#include <string>
#include <iostream>
#include "Symbol.h"
using namespace std;

class Node;
class StartNode;
class ProgramNode;
class BlockNode;
class StatementGroupNode;
class StatementNode;
class DeclarationStatementNode;
class IdentifierNode;
class AssignmentStatementNode;
class ExpressionNode;
class CoutStatementNode;
class IntegerNode;
class BinaryOperatorNode;
class PlusNode;
class MinusNode;
class TimesNode;
class DividesNode;
class LessEqualNode;
class GreaterNode;
class GreaterEqualNode;
class AssignmentNode;
class NotEqualNode;

// Node class ------

class Node{

public:
    virtual ~Node();
    virtual void Interpret();
};

// StartNode class ------

class StartNode: public Node{

public:
    StartNode(ProgramNode*);
    ~StartNode();
    void Interpret();
private:
    ProgramNode * mProgramNode;
};

// ProgramNode class ------

class ProgramNode: public Node{

public:
    ProgramNode(BlockNode*);
    ~ProgramNode();
    void Interpret();
private:
    BlockNode * mBlockNode;
};

// StatementGroupNode class ------

class StatementGroupNode: public Node{

public:
    ~StatementGroupNode();
    void AddStatement(StatementNode*);
    void Interpret();

private:
    vector<StatementNode*> snVector;
};

// StatementNode class ------

class StatementNode: public Node{
public:
private:
};

// BlockNode class ------

class BlockNode: public StatementNode{

public:
    BlockNode(StatementGroupNode*);
    ~BlockNode();
    void Interpret();
private:
    StatementGroupNode * mStatementGroupNode;
};

// IfStatementNode class -------

class IfStatementNode: public StatementNode{
public:
    IfStatementNode(ExpressionNode* en, StatementNode* sn, StatementNode* sn2);
    ~IfStatementNode();
    void Interpret();
private:
    ExpressionNode * mExpressionNode;
    StatementNode * mStatementNode;
    StatementNode * mStatementNode2;
};

// WhileStatementNode class ------

class WhileStatementNode: public StatementNode{
public:
    WhileStatementNode(ExpressionNode* en, StatementNode* sn);
    ~WhileStatementNode();
    void Interpret();
private:
    ExpressionNode * mExpressionNode;
    StatementNode * mStatementNode;
};

// RepeatStatementNode class ------

class RepeatStatementNode: public StatementNode{
public:
    RepeatStatementNode(ExpressionNode* en, StatementNode* sn);
    ~RepeatStatementNode();
    void Interpret();
private:
    ExpressionNode * mExpressionNode;
    StatementNode * mStatementNode;
};

// DeclarationStatementNode class -------

class DeclarationStatementNode: public StatementNode{

public:
    DeclarationStatementNode(IdentifierNode *, ExpressionNode *);
    ~DeclarationStatementNode();
    void Interpret();
private:
    IdentifierNode * mIdentifierNode;
    ExpressionNode * mExpressionNode;
};

// AssignmentStatementNode class -------

class AssignmentStatementNode: public StatementNode{

public:
    AssignmentStatementNode(IdentifierNode *, ExpressionNode *);
    ~AssignmentStatementNode();
    void Interpret();
private:
    IdentifierNode * mIdentifierNode;
    ExpressionNode * mExpressionNode;
};

// Cout Statement Class ------
class CoutStatementNode: public StatementNode{

public:
    CoutStatementNode(ExpressionNode *);
    ~CoutStatementNode();
    void Interpret();
private:
    ExpressionNode * mExpressionNode;
};

// Expression Node Class

class ExpressionNode{
public:
    virtual ~ExpressionNode();
    virtual int Evaluate()=0;

private:
};

// Identifier Node Class
class IdentifierNode: public ExpressionNode{
public:
    IdentifierNode(std::string s, SymbolTableClass *symbolTable);
    void DeclareVariable();
    void SetValue(int v);
    int GetIndex();
    virtual int Evaluate();
private:
    string mLabel;
    SymbolTableClass *mSymbolTable;
};

// Integer Node Class
class IntegerNode: public ExpressionNode{
public:
    IntegerNode(int);
    int Evaluate();
private:
    int mIntegerNode;
};

// Binary Operator Node
class BinaryOperatorNode: public ExpressionNode{
public:
    BinaryOperatorNode(ExpressionNode* l, ExpressionNode* r);
    ~BinaryOperatorNode();
protected:
    ExpressionNode * mLeft;
    ExpressionNode * mRight;
};

// Or Node
class OrNode: public BinaryOperatorNode{
public:
    OrNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// And Node
class AndNode: public BinaryOperatorNode{
public:
    AndNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// Plus Node
class PlusNode: public BinaryOperatorNode{
public:
    PlusNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// Minus Node
class MinusNode: public BinaryOperatorNode{
public:
    MinusNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// Times Node
class TimesNode: public BinaryOperatorNode{
public:
    TimesNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// Divide Node
class DivideNode: public BinaryOperatorNode{
public:
    DivideNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// Exponent Node
class ExponentNode: public BinaryOperatorNode{
public:
    ExponentNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// Less Node
class LessNode: public BinaryOperatorNode{
public:
    LessNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// LessEqual Node
class LessEqualNode: public BinaryOperatorNode{
public:
    LessEqualNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// Greater Node
class GreaterNode: public BinaryOperatorNode{
public:
    GreaterNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// GreaterEqual Node
class GreaterEqualNode: public BinaryOperatorNode{
public:
    GreaterEqualNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// Equal Node
class EqualNode: public BinaryOperatorNode{
public:
    EqualNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

// NotEqual Node
class NotEqualNode: public BinaryOperatorNode{
public:
    NotEqualNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};

//Bitwise And
class BitwiseAndNode: public BinaryOperatorNode{
public:
    BitwiseAndNode(ExpressionNode* left, ExpressionNode* right)
        : BinaryOperatorNode(left, right){};
    int Evaluate();
private:
};
#endif // NODE
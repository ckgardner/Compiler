#include "Node.h"

Node::~Node(){}
void Node::Interpret(){}

// START NODE
StartNode::StartNode(ProgramNode* node){
    mProgramNode = node;
}
StartNode::~StartNode(){
    delete mProgramNode;
}
void StartNode::Interpret(){
    mProgramNode->Interpret();
}

// PROGRAM NODE
ProgramNode::ProgramNode(BlockNode* bn){
    mBlockNode = bn;
}
ProgramNode::~ProgramNode(){
    delete mBlockNode;
}
void ProgramNode::Interpret(){
    mBlockNode->Interpret();
}

// BLOCK NODE
BlockNode::BlockNode(StatementGroupNode* sgn){
    mStatementGroupNode = sgn;
}
BlockNode::~BlockNode(){
    delete mStatementGroupNode;
}
void BlockNode::Interpret(){
    mStatementGroupNode->Interpret();
}

// STATEMENTGROUP NODE
StatementGroupNode::~StatementGroupNode(){
    for(int i=0;i<snVector.size();i++){
        delete snVector[i];
    }
}
void StatementGroupNode::AddStatement(StatementNode* sn){
    snVector.push_back(sn);
}
void StatementGroupNode::Interpret(){
    for(int i=0;i<snVector.size();i++){
        snVector[i]->Interpret();
    }
}

// IFSTATEMENT NODE
IfStatementNode::IfStatementNode(ExpressionNode * en, StatementNode * sn, StatementNode * sn2){
    mExpressionNode = en;
    mStatementNode = sn;
    mStatementNode2 = sn2;
}
IfStatementNode::~IfStatementNode(){
    delete mExpressionNode;
    delete mStatementNode;
    delete mStatementNode2;
}
void IfStatementNode::Interpret(){
    if( mExpressionNode->Evaluate() != 0) {
        mStatementNode->Interpret();
    }else if(mStatementNode2 != NULL){
        mStatementNode2->Interpret();
    }
}

 // WHILESTATEMENT NODE
WhileStatementNode::WhileStatementNode(ExpressionNode * en, StatementNode * sn){
    mExpressionNode = en;
    mStatementNode = sn;
}
WhileStatementNode::~WhileStatementNode(){
    delete mExpressionNode;
    delete mStatementNode;
}
void WhileStatementNode::Interpret(){
    while( this->mExpressionNode->Evaluate()) {
        mStatementNode->Interpret();
    }
}

 // WHILESTATEMENT NODE
RepeatStatementNode::RepeatStatementNode(ExpressionNode * en, StatementNode * sn){
    mExpressionNode = en;
    mStatementNode = sn;
}
RepeatStatementNode::~RepeatStatementNode(){
    delete mExpressionNode;
    delete mStatementNode;
}
void RepeatStatementNode::Interpret(){
    int val = this->mExpressionNode->Evaluate();
    for(int i=0;i<val;i++){
        mStatementNode->Interpret();
    }
}

// DECLARATIONSTATEMENT NODE
DeclarationStatementNode::DeclarationStatementNode(IdentifierNode* in, ExpressionNode* en){
    mIdentifierNode = in;
    mExpressionNode = en;
}
DeclarationStatementNode::~DeclarationStatementNode(){
    delete mIdentifierNode;
    delete mExpressionNode;
}
void DeclarationStatementNode::Interpret(){
    mIdentifierNode->DeclareVariable();
    if( mExpressionNode != NULL) {
        int val = mExpressionNode->Evaluate();
        mIdentifierNode->SetValue(val);
    }
}

// ASSIGNMENTSTATEMENT NODE
AssignmentStatementNode::AssignmentStatementNode(IdentifierNode * in, ExpressionNode * en){
    mIdentifierNode = in;
    mExpressionNode = en;
}
AssignmentStatementNode::~AssignmentStatementNode(){
    delete mIdentifierNode;
    delete mExpressionNode;
}
void AssignmentStatementNode::Interpret(){
    int val = mExpressionNode->Evaluate();
    mIdentifierNode->SetValue(val);
}

// COUTSTATEMENT NODE
CoutStatementNode::CoutStatementNode(ExpressionNode * en){
    mExpressionNode = en;
}
CoutStatementNode::~CoutStatementNode(){
    delete mExpressionNode;
}
void CoutStatementNode::Interpret(){
    int val = mExpressionNode->Evaluate();
    cout << "\tInterpreter returned: " << val << '\n';
}

// INTEGER NODE
IntegerNode::IntegerNode(int i){
    mIntegerNode = i;
}
int IntegerNode::Evaluate(){
    return mIntegerNode;
}

// EXPRESSION NODE
ExpressionNode::~ExpressionNode(){}


// IDENTIFIER NODE
IdentifierNode::IdentifierNode(std::string s, SymbolTableClass * symbolTable)
{
	mLabel = s;
	mSymbolTable = symbolTable;
}
void IdentifierNode::DeclareVariable(){
    mSymbolTable->AddEntry(mLabel);
}
void IdentifierNode::SetValue(int v){
    mSymbolTable->SetValue(mLabel, v);
}
int IdentifierNode::GetIndex(){
    return mSymbolTable->GetIndex(mLabel);
}
int IdentifierNode::Evaluate(){
    return mSymbolTable->GetValue(mLabel);
}

// BINARY OPERATOR NODE
BinaryOperatorNode::BinaryOperatorNode(ExpressionNode* l, ExpressionNode* r){
    mLeft = l;
    mRight = r;
}
BinaryOperatorNode::~BinaryOperatorNode(){
    delete mLeft;
    delete mRight;
}

// OR NODE
int OrNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    return l||r;
}

// AND NODE
int AndNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    return l&&r;
}

// PLUS NODE
int PlusNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    return l+r;
}

// Minus NODE
int MinusNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    return l-r;
}

// Times NODE
int TimesNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    return l*r;
}

// Divide NODE
int DivideNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    return l/r;
}

// Exponent NODE
int ExponentNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    return pow(l, r);
}

// Less NODE
int LessNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    if (l < r){
        return 1;
    }else{
        return 0;
    }
}

// LESSEQUAL NODE
int LessEqualNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    if (l <= r){
        return 1;
    }else{
        return 0;
    }
}

// GREATER NODE
int GreaterNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    if (l > r){
        return 1;
    }else{
        return 0;
    }
}

// GREATEREQUAL NODE
int GreaterEqualNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    if (l >= r){
        return 1;
    }else{
        return 0;
    }
}

// EQUAL NODE
int EqualNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    if (l == r){
        return 1;
    }else{
        return 0;
    }
}

// NOTEQUAL NODE
int NotEqualNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    if (l != r){
        return 1;
    }else{
        return 0;
    }
}

// BITWISE AND
int BitwiseAndNode::Evaluate(){
    int l = mLeft->Evaluate();
    int r = mRight->Evaluate();
    return l & r;
}
#include "StateMachine.h"
#include <iostream>
#include <iomanip>

StateMachineClass::StateMachineClass(){
    mCurrentState = START_STATE;
    // First, initialize all the mLegalMoves to CANTMOVE_STATE
    // Then, reset the mLegalMoves that are legitimate
    for(int i=0; i<LAST_STATE; i++){
        for(int j=0; j<LAST_CHAR; j++){
            mLegalMoves[i][j] = CANTMOVE_STATE;
        }
    }
    mLegalMoves[START_STATE][DIGIT_CHAR]= INTEGER_STATE; // S -> DIGIT
    mLegalMoves[INTEGER_STATE][DIGIT_CHAR]= INTEGER_STATE;
    mLegalMoves[START_STATE][PLUS_CHAR]= PLUS_STATE;
    mLegalMoves[START_STATE][MINUS_CHAR]= MINUS_STATE;
    mLegalMoves[START_STATE][SEMICOLON_CHAR]= SEMICOLON_STATE;
    mLegalMoves[START_STATE][LESS_CHAR]= LESS_STATE;
    mLegalMoves[LESS_STATE][LESS_CHAR]= INSERTION_STATE;
    mLegalMoves[LESS_STATE][ASSIGNMENT_CHAR]= LESSEQUAL_STATE;
    mLegalMoves[START_STATE][GREATER_CHAR]= GREATER_STATE;
    mLegalMoves[GREATER_STATE][ASSIGNMENT_CHAR]= GREATEREQUAL_STATE;
    mLegalMoves[START_STATE][ASSIGNMENT_CHAR]= ASSIGNMENT_STATE;
    mLegalMoves[ASSIGNMENT_STATE][ASSIGNMENT_CHAR]= EQUAL_STATE;
    mLegalMoves[START_STATE][DIVIDE_CHAR]= DIVIDE_STATE;
    mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LINE_COMMENT_STATE;

    mLegalMoves[DIVIDE_STATE][TIMES_CHAR]= COMMENT_STATE;

    mLegalMoves[START_STATE][TIMES_CHAR] = TIMES_STATE;
    mLegalMoves[TIMES_STATE][TIMES_CHAR] = EXPONENT_STATE;
    mLegalMoves[START_STATE][LPAREN_CHAR]= LPAREN_STATE;
    mLegalMoves[START_STATE][RPAREN_CHAR]= RPAREN_STATE;
    mLegalMoves[START_STATE][LCURLY_CHAR]= LCURLY_STATE;
    mLegalMoves[START_STATE][RCURLY_CHAR]= RCURLY_STATE;
    mLegalMoves[START_STATE][LETTER_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[IDENTIFIER_STATE][DIGIT_CHAR]= IDENTIFIER_STATE;
    mLegalMoves[START_STATE][EOF_CHAR]= EOF_STATE;
    mLegalMoves[START_STATE][WHITESPACE_CHAR]= START_STATE;
    mLegalMoves[START_STATE][NOTEQUAL_CHAR]= NOT_STATE;
    mLegalMoves[NOT_STATE][ASSIGNMENT_CHAR]= NOTEQUAL_STATE;

    mLegalMoves[START_STATE][NEWL_CHAR]= START_STATE;

    // And and Or Statements
    mLegalMoves[START_STATE][AND_CHAR] = BITWISE_AND_STATE;
    mLegalMoves[START_STATE][OR_CHAR] = ALMOST_OR_STATE;
    mLegalMoves[BITWISE_AND_STATE][AND_CHAR] = AND_STATE;
    mLegalMoves[ALMOST_OR_STATE][OR_CHAR] = OR_STATE;

    // Line Comments:
    for(int j=0; j<LAST_CHAR; j++){
        mLegalMoves[LINE_COMMENT_STATE][j] = LINE_COMMENT_STATE;
    }
    mLegalMoves[LINE_COMMENT_STATE][NEWL_CHAR] = START_STATE;
    mLegalMoves[LINE_COMMENT_STATE][EOF_CHAR] = EOF_STATE;

    /* Group Comments*/
    for(int j=0; j<LAST_CHAR; j++){
        mLegalMoves[COMMENT_STATE][j] = COMMENT_STATE;
    }
    mLegalMoves[COMMENT_STATE][TIMES_CHAR]= CLOSING_COMMENT_STATE;
    mLegalMoves[COMMENT_STATE][EOF_CHAR] = EOF_STATE;

    for(int j=0; j<LAST_CHAR; j++){
        mLegalMoves[CLOSING_COMMENT_STATE][j] = COMMENT_STATE;
    }
    mLegalMoves[CLOSING_COMMENT_STATE][DIVIDE_CHAR]= START_STATE;
    mLegalMoves[CLOSING_COMMENT_STATE][EOF_CHAR] = EOF_STATE;

    // First, initialize all states to correspond to the BAD token type.
    // Then, reset the end states to correspond to the correct token types.
    for(int i=0; i<LAST_STATE; i++){
        mCorrespondingTokenTypes[i]=BAD_TOKEN;
    }
    mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
    mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
    mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
    mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
    mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
    mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
    mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
    mCorrespondingTokenTypes[TIMES_STATE] = TIMES_TOKEN;
    mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
    mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
    mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
    mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
    mCorrespondingTokenTypes[EOF_STATE] = ENDFILE_TOKEN;
    mCorrespondingTokenTypes[LESS_STATE] = LESS_TOKEN;
    mCorrespondingTokenTypes[GREATER_STATE] = GREATER_TOKEN;
    mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
    mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
    mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
    mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN; 
    mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
    mCorrespondingTokenTypes[AND_STATE] = AND_TOKEN;
    mCorrespondingTokenTypes[OR_STATE] = OR_TOKEN;
    mCorrespondingTokenTypes[EXPONENT_STATE] = EXPONENT_TOKEN;
    mCorrespondingTokenTypes[BITWISE_AND_STATE] = BITWISE_AND_TOKEN;
};

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType &correspondingTokenType){
    CharacterType chartype = BAD_CHAR;
    if(isdigit(currentCharacter)){
        chartype = DIGIT_CHAR;
    }
    if(isalpha(currentCharacter)){
        chartype = LETTER_CHAR;
    }
    if(isspace(currentCharacter)){
        chartype = WHITESPACE_CHAR;
    }
    if(currentCharacter == '+'){
        chartype = PLUS_CHAR;
    }
    if(currentCharacter == '-'){
        chartype = MINUS_CHAR;
    }
    if(currentCharacter == ';'){
        chartype = SEMICOLON_CHAR; 
    }
    if(currentCharacter == '<'){
        chartype = LESS_CHAR;
    }
    if(currentCharacter == '>'){
        chartype = GREATER_CHAR; 
    }
    if(currentCharacter == '/'){
        chartype = DIVIDE_CHAR;
    }
    if(currentCharacter == '('){
        chartype = LPAREN_CHAR;;
    }
    if(currentCharacter == ')'){
        chartype = RPAREN_CHAR;;
    }
    if(currentCharacter == '{'){
        chartype = LCURLY_CHAR;;
    }
    if(currentCharacter == '}'){
        chartype = RCURLY_CHAR;
    }
    if(currentCharacter == '\n'){
        chartype = NEWL_CHAR;
    }
    if(currentCharacter == '*'){
        chartype = TIMES_CHAR;
    }
    if(currentCharacter == '='){
        chartype = ASSIGNMENT_CHAR;
    }
    if(currentCharacter == '&'){
        chartype = AND_CHAR;
    }
    if(currentCharacter == '|'){
        chartype = OR_CHAR;
    }
    if(currentCharacter == EOF){
        chartype = EOF_CHAR; 
    }

    correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
    mCurrentState = mLegalMoves[mCurrentState][chartype];
    return mCurrentState;
}
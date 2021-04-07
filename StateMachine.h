#ifndef STATE_MACHINE
#define STATE_MACHINE
#include <string>
#include <iostream>
#include "Token.h"

enum MachineState {
    START_STATE, IDENTIFIER_STATE, INTEGER_STATE, PLUS_STATE, CANTMOVE_STATE, 
    BAD_STATE, LESS_STATE, GREATER_STATE, EOF_STATE, COMMENT_STATE,
    SEMICOLON_STATE, DIVIDE_STATE, LPAREN_STATE, RPAREN_STATE, 
    RCURLY_STATE, LCURLY_STATE, MINUS_STATE, TIMES_STATE, INSERTION_STATE, 
    LINE_COMMENT_STATE, CLOSING_COMMENT_STATE, LESSEQUAL_STATE, GREATEREQUAL_STATE,
    ASSIGNMENT_STATE, EQUAL_STATE, NOT_STATE, NOTEQUAL_STATE, AND_STATE, OR_STATE, BITWISE_AND_STATE, ALMOST_OR_STATE, EXPONENT_STATE,
    LAST_STATE
};
enum CharacterType {
    LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, PLUS_CHAR, 
    BAD_CHAR, LESS_CHAR, GREATER_CHAR, EOF_CHAR, NEWL_CHAR,
    SEMICOLON_CHAR, DIVIDE_CHAR, LPAREN_CHAR, RPAREN_CHAR,
    RCURLY_CHAR, LCURLY_CHAR, MINUS_CHAR, TIMES_CHAR,
    ASSIGNMENT_CHAR, EQUAL_CHAR, NOTEQUAL_CHAR, AND_CHAR, OR_CHAR,
    LAST_CHAR
};

class StateMachineClass
{
public:
    StateMachineClass();
    MachineState UpdateState(char currentCharacter, TokenType &correspondingTokenType);
private:
    MachineState mCurrentState;
    // The matrix of legal moves:
    MachineState mLegalMoves[LAST_STATE][LAST_CHAR];
    // Which end-machine-states correspond to which token types.
    // (non end states correspond to the BAD_TOKEN token type)
    TokenType mCorrespondingTokenTypes[LAST_STATE];
};

#endif // STATE_MACHINE
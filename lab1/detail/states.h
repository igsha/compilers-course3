#ifndef DETAIL_STATES_H
#define DETAIL_STATES_H

#include "detail/tokentype.h"

#include <unordered_map>

enum class States {
    None,
    Init,
    NumInt,
    NumDot,
    NumExp,
    NumSign,
    NumFrac,
    Op,
    Id,
    LPar,
    RPar,
    Comma,
    Blank,
    Count,
};

// no ABI compatible
extern std::unordered_map<States, TokenType> stateToTokenType;
extern std::unordered_map<States, States(*)(unsigned char)> transitionTable;
extern std::unordered_map<States, bool> acceptStateTable;

#endif  // DETAIL_STATES_H

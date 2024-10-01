#ifndef DETAIL_TOKEN_TYPE_H
#define DETAIL_TOKEN_TYPE_H

#include "tokentype.h"

#include <ostream>

enum class TokenType {
    Error,
    Number,
    Operator,
    Id,
    LParen,
    RParen,
    Comma,
    Blank,
};

std::ostream& operator<<(std::ostream& os, TokenType t);

#endif  // DETAIL_TOKEN_TYPE_H

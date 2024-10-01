#ifndef LEXER_H
#define LEXER_H

#include <ostream>
#include <string_view>

#include "detail/tokentype.h"

struct Token {
    TokenType type;
    std::string_view view;

    friend std::ostream& operator<<(std::ostream& os, Token t);

    static Token consume(std::string_view input);
};

#endif  // LEXER_H

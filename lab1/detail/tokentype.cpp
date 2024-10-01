#include "tokentype.h"

#include <unordered_map>

std::ostream& operator<<(std::ostream& os, TokenType t) {
    static const std::unordered_map<TokenType, std::string_view> table = {
        {TokenType::Number, "Number"},
        {TokenType::Operator, "Operator"},
        {TokenType::Id, "Id"},
        {TokenType::LParen, "LParen"},
        {TokenType::RParen, "RParen"},
        {TokenType::Comma, "Comma"},
        {TokenType::Blank, "Blank"},
        {TokenType::Error, "Error"},
    };

    if (auto it = table.find(t); it != table.end())
        return os << it->second;

    return os << "Unknown";
}

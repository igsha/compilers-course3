#include "states.h"

#include <cctype>

namespace {

bool ismyalpha(unsigned char ch) {
    return (std::isalpha(ch) && std::islower(ch)) || ch == '_';
}

States transitFromNone(unsigned char) {
    return States::None;
}

States transitFromInit(unsigned char symbol) {
    if (ismyalpha(symbol))
        return States::Id;
    else if (symbol == '(')
        return States::LPar;
    else if (symbol == '(')
        return States::RPar;
    else if (symbol == ',')
        return States::Comma;
    else if (std::string_view{"+-/*^"}.contains(symbol))
        return States::Op;
    else if (std::isdigit(symbol))
        return States::NumInt;
    else if (std::isblank(symbol))
        return States::Blank;
    else
        return States::None;
}

States transitFromNumInt(unsigned char symbol) {
    if (std::isdigit(symbol))
        return States::NumInt;
    else if (symbol == '.')
        return States::NumDot;
    else if (std::tolower(symbol) == 'e')
        return States::NumExp;
    else
        return States::None;
}

States transitFromNumDot(unsigned char symbol) {
    if (std::isdigit(symbol))
        return States::NumDot;
    else if (std::tolower(symbol) == 'e')
        return States::NumExp;
    else
        return States::None;
}

States transitFromNumExp(unsigned char symbol) {
    if (symbol == '+' || symbol == '-')
        return States::NumSign;
    else if (std::isdigit(symbol))
        return States::NumFrac;
    else
        return States::None;
}

States transitFromNumSign(unsigned char symbol) {
    return std::isdigit(symbol) ? States::NumFrac : States::None;
}

States transitFromNumFrac(unsigned char symbol) {
    return std::isdigit(symbol) ? States::NumFrac : States::None;
}

States transitFromId(unsigned char symbol) {
    return ismyalpha(symbol) || std::isdigit(symbol) ? States::Id : States::None;
}

States transitFromBlank(unsigned char symbol) {
    return std::isblank(symbol) ? States::Blank : States::None;
}

}

std::unordered_map<States, States(*)(unsigned char)> transitionTable = {
    {States::None, transitFromNone},
    {States::Init, transitFromInit},
    {States::NumInt, transitFromNumInt},
    {States::NumDot, transitFromNumDot},
    {States::NumExp, transitFromNumExp},
    {States::NumSign, transitFromNumSign},
    {States::NumFrac, transitFromNumFrac},
    {States::Op, transitFromNone},
    {States::Id, transitFromId},
    {States::LPar, transitFromNone},
    {States::RPar, transitFromNone},
    {States::Comma, transitFromNone},
    {States::Blank, transitFromBlank},
};

std::unordered_map<States, TokenType> stateToTokenType = {
    {States::None, TokenType::Error},
    {States::Init, TokenType::Error},
    {States::NumInt, TokenType::Number},
    {States::NumDot, TokenType::Number},
    {States::NumExp, TokenType::Error},
    {States::NumSign, TokenType::Error},
    {States::NumFrac, TokenType::Number},
    {States::Op, TokenType::Operator},
    {States::Id, TokenType::Id},
    {States::LPar, TokenType::LParen},
    {States::RPar, TokenType::RParen},
    {States::Comma, TokenType::Comma},
    {States::Blank, TokenType::Blank},
};

std::unordered_map<States, bool> acceptStateTable = {
    {States::None, false},
    {States::Init, false},
    {States::NumInt, true},
    {States::NumDot, true},
    {States::NumExp, false},
    {States::NumSign, false},
    {States::NumFrac, true},
    {States::Op, true},
    {States::Id, true},
    {States::LPar, true},
    {States::RPar, true},
    {States::Comma, true},
    {States::Blank, true},
};

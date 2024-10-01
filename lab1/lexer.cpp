#include "lexer.h"

#include "detail/states.h"

std::ostream& operator<<(std::ostream& os, Token t) {
    return os << t.type << " [" << t.view << "]";
}

Token Token::consume(std::string_view input) {
    States state = States::Init;
    States lastState = States::None;
    auto lastIter = input.begin();
    for (auto it = input.begin(); it != input.end() && state != States::None; ++it) {
        state = transitionTable.at(state)(*it);
        if (acceptStateTable.at(state)) {
            lastState = state;
            lastIter = it;
        }
    }

    return {stateToTokenType.at(lastState), std::string_view{input.begin(), lastIter + 1}};
}

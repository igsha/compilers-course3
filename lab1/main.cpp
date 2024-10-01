#include <iostream>

#include <lexer.h>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        auto input = std::string_view{argv[i]};
        while (!input.empty()) {
            auto token = Token::consume(input);
            std::cout << token << "\n";
            input.remove_prefix(token.view.size());
        }
    }

    return 0;
}

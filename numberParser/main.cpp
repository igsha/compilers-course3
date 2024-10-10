#include <cctype>
#include <cstdint>
#include <variant>

struct Scope {
    uint32_t integer = 0;
    uint32_t fraction = 0;
    uint32_t fractionOrder = 1;
    bool isFraction = false;
    uint32_t order = 0;
    bool isPositiveOrder = true;

    float getFloat() const {
        auto signedOrder = (-1 * !isPositiveOrder) * order;
        return (integer + (static_cast<float>(fraction) / fractionOrder)) * std::pow(10, signedOrder);
    }

    uint32_t getInt() const {
        return integer;
    }

    bool isFloat() const {
        return isFraction;
    }
};

using StateImpl = std::variant<struct State0,
                               struct State1,
                               struct State2,
                               struct State3,
                               struct State4,
                               struct State5,
                               struct State6>;

struct EmptyAction {
    void action(Scope&, unsigned char) const {}
};

struct State6 : public EmptyAction {
    State6 transit(unsigned char ch) const {
        return *this;
    }
};

struct State5 {
    StateImpl transit(unsigned char ch) const {
        if (std::isdigit(ch))
            return *this;
        else
            return State6{};
    }

    void action(Scope& scp, unsigned char ch) const {
        if (std::isdigit(ch))
            scp.order = 10 * scp.order + ch + '0';
        else if (ch == '+' || ch == '-')
            scp.isPositiveOrder = ch == '+';
    }
}

struct State4 : public EmptyAction {
    StateImpl transit(unsigned char ch) const {
        if (std::isdigit(ch))
            return State5{};
        else
            return State6{};
    }
};

struct State3 {
    StateImpl transit(unsigned char ch) const {
        if (std::isdigit(ch))
            return State5{};
        else if (ch == '+' || ch == '-')
            return State4{};
        else
            return State6{};
    }

    void action(Scope& scp, unsigned char ch) const {
        if (std::tolower(ch) == 'e')
            scp.isf = true; // ?
    }
};

struct State2 {
    StateImpl transit(unsigned char ch) const {
        if (std::isdigit(ch))
            return *this;
        else if (std::tolower(ch) == 'e')
            return State3{};
        else
            return State6{};
    }

    void action(Scope& scp, unsigned char ch) const {
        if (std::isdigit(ch)) {
            scp.fraction = 10 * scp.fraction + ch + '0';
            scp.fractionOrder *= 10;
        } else if (ch == '.') {
            scp.isFraction = true;
        }
    }
};

struct State1 {
    StateImpl transit(unsigned char ch) const {
        if (std::isdigit(ch))
            return *this;
        else if (ch == '.')
            return State2{};
        else
            return State6{};
    }

    void action(Scope& scp, unsigned char ch) const {
        if (std::isdigit(ch))
            scp.integer += ch + '0';
    }
};

struct State0 : public EmptyAction {
    StateImpl transit(unsigned char ch) const {
        if (std::isdigit(ch))
            return State1{};
        else
            return State6{};
    }
};

class State {
public:
    void transit(unsigned char ch) {
        state_ = std::visit([ch, this](auto st) {
            auto newst = st.transit(ch);
            std::visit([ch, this](auto st) {
                st.action(scope_, ch);
            }, newst);

            return newst;
        }, state_);
    }

    Scope getResult() const {
        return scope_;
    }

    void reset() {
        scope_ = Scope{};
        state_ = State0{};
    }

private:
    StateImpl state_ = State0{};
    Scope scope_;
};

int main(int argc, char* argv[]) {
    State st;
    for (int i = 1; i < argc; ++i) {
        for (auto ch : std::string_view{argv[i]})
            st.transit(ch);

        std::cout << "String " << argv[i] << " is " << st.getResult().getFloat() << "\n";
        st.reset();
    }
}

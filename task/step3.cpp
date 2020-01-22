#include <iostream>

template<typename Input, typename UnaryPredicate>
class filter_helper {
    const Input &input;
    const UnaryPredicate &p;

    class iterator {
        const filter_helper &owner;
        typename Input::const_iterator current;
    public:
        explicit iterator(const filter_helper &owner_) : owner(owner_),
                                                         current(std::find_if(std::cbegin(owner.input),
                                                                              std::cend(owner.input),
                                                                              owner.p)) {};

        auto operator!=(typename Input::const_iterator rhs) const { return current != rhs; };

        auto operator++() { return current = std::find_if(++current, std::cend(owner.input), owner.p); };

        auto operator*() const { return *current; };
    };

public:
    explicit filter_helper(const Input &input_, const UnaryPredicate &p) : input(input_), p(p) {}

    auto begin() const { return iterator{*this}; }

    auto end() const { return std::cend(input); }
};

template<typename UnaryPredicate>
struct filter : UnaryPredicate {
    filter(UnaryPredicate p) : UnaryPredicate(p) {};
};

template<typename Input, typename F>
auto operator|(const Input &input, const F &f) { return filter_helper(input, f); }

int main() {
    const std::string s{"hello"};

    for (auto i: s | filter{[](auto c) { return c != 'l'; }}) {
        std::cout << i << std::endl;
    }
}

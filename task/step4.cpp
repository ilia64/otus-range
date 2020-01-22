#include <iostream>

template<typename Input, typename UnaryPredicate>
class filter_helper {
    const Input &input;
    const UnaryPredicate &p;

    class iterator {
        const filter_helper *owner;
        typename Input::const_iterator current;
    public:
        explicit iterator(const filter_helper &owner_, typename Input::const_iterator current_) : owner(&owner_),
                                                                                                  current(std::find_if(current_,
                                                                                                                       std::cend(owner_.input),
                                                                                                                       owner_.p)) {};
        auto operator!=(const iterator &rhs) const { return current != rhs.current; };

        auto &operator++() {
            current = std::find_if(++current, std::cend(owner->input), owner->p);
            return *this;
        };

        auto operator*() const { return *current; };
    };

public:
    using const_iterator = iterator;

    explicit filter_helper(const Input &input_, const UnaryPredicate &p) : input(input_), p(p) {}

    auto begin() const { return iterator{*this, std::cbegin(input)}; }

    auto end() const { return iterator{*this, std::cend(input)}; }
};

template<typename UnaryPredicate>
struct filter : UnaryPredicate {
    filter(UnaryPredicate p) : UnaryPredicate(p) {};
};

template<typename Input, typename F>
auto operator|(const Input &input, const F &f) { return filter_helper(input, f); }

int main() {
    const std::string s{"hello"};

    for (auto i: s | filter{[](auto c) { return c != 'l'; }} | filter{[](auto c) { return c != 'h'; }}) {
        std::cout << i << std::endl;
    }
}

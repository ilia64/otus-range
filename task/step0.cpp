#include <iostream>
#include <string>

template<typename Input>
class filter_helper
{
    const Input &input;

    class iterator {
        typename Input::const_iterator current;
    public:
        explicit iterator(typename Input::const_iterator current_) : current(current_) {};

        auto operator!=(typename Input::const_iterator rhs) const { return current != rhs; };

        auto operator++() { return ++current; };

        auto &operator*() const { return *current; };
    };


public:
    explicit filter_helper(const Input &input_) : input(input_) {}

    auto begin() const { return iterator{std::cbegin(input)}; }

    auto end() const { return std::cend(input); }
};

int main() {
    const std::string s{"hello"};

    for (auto i: filter_helper{s}) {
        std::cout << i << std::endl;
    }
}

#include <range/v3/all.hpp>
#include <iostream>

int main() {
    const std::string s{"hello"};

    ranges::for_each(s | ranges::view::filter([](auto c) { return c == 'l'; }),
            [](auto i) { std::cout << i << std::endl; });
}

[](auto i) { std::cout << i << std::endl; }(42);
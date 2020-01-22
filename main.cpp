#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <string>
#include <array>
#include <set>
#include <vector>
#include <range/v3/all.hpp>

using namespace ranges;

using Octet = unsigned char;
using Address = std::array<Octet, 4>;
using Pool = std::multiset<Address>;
using PoolUnique = std::set<Address>;

auto octet_to_string = [](const Octet& octet) { return std::to_string(octet); };

std::ostream& operator<< (std::ostream &out, const Address& address)
{
    auto a = address | view::transform(octet_to_string) | view::intersperse(".");
    for_each(a, [&out](const auto& str) { out << str; });
    return out;
}

template <typename Iter, typename D>
Address split(Iter begin, Iter end, D delimiter)
{
    Address address;

    size_t index = 0;
    while (begin != end)
    {
        Iter pos = std::find(begin, end, delimiter);
        int chunk = std::stoi(std::string(begin, pos));
        assert(chunk >= 0 && chunk <= 255);
        address[index++] = static_cast<Octet>(chunk);
        begin = (pos == end) ? end : std::next(pos);
    }

    assert(index == 4);
    return address;
}

template <typename T>
void print (const T& pool)
{
    for_each(pool | view::reverse, [](const auto& address) { std::cout << address << '\n'; });
}

void print_with_filter(const Pool& pool, std::function<bool(const Address& address)> handler)
{
    print (pool | view::filter(handler) | to_vector);
}

int main()
{
    try
    {
        Pool pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            if (line.empty())
            {
                break;
            }

            auto pos = std::find(line.begin(), line.end(), '\t');
            Address address = split(line.begin(), pos, '.');

            for (size_t i = 0; i < 4; i++)
            {
                Octet octet = address[i];
            }

            pool.insert(address);
        }

        //cat bin/ip_filter.tsv | bin/ip_filter

        print(pool);
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        std::cout << std::endl;
        print_with_filter(pool, [](const Address& address) { return address[0] == 1; });
        //std::cout << filter(rIndex, 1) << std::endl;
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        std::cout << std::endl;
        print_with_filter(pool, [](const Address& address) { return address[0] == 46 && address[1] == 70; });
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        std::cout << std::endl;
        print_with_filter(pool, [](const Address& address)
        {
            return any_of(address, [](Octet octet) {return octet == 46;});
        });
        //std::cout << filter<true>(rIndex, 46) << std::endl;
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

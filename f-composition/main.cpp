#include <iostream>
#include <typeinfo>
#include <stdint.h>
#include <vector>


#include "functional.hpp"   // (f * g)(t) == f(g(t))
#include "pretty_print.hpp" // ostream << vector


int main()
{
    std::vector<int> const vec{1,2,3,4,5};

    auto const dec = [](int const& v) {
        return v-1;
    };
    auto const sq = [](int const& v) {
        return v*v;
    };
    
    std::vector<int> const transformed_vec{ dec * sq * vec };

    std::cout << "Orig: \t" << vec              << '\n';
    std::cout << "Sq:   \t" << sq * vec         << '\n';
    std::cout << "Sq-1: \t" << transformed_vec  << "\n\n";

    std::cout << "Const:\t" << sq*dec*7         << std::endl;
}

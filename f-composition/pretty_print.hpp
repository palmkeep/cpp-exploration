#ifndef PRETTY_PRINT_H
#define PRETTY_PRINT_H

#include <iostream>
#include <iomanip>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> const& vec)
{
    if (vec.size() == 0) { return os; } // Empty
    os << "[" << vec[0];                // First

    if (1 < vec.size()) {               // Rest
        for (auto it = ++vec.cbegin(); it != vec.cend(); ++it) {
            os << ", " << std::setw(2) << *it;
        }
    }

    os << "]";

    return os;
}


#endif

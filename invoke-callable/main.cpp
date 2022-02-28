#include "invoke_callable.hpp"
#include <iostream>
#include <vector>

/*
 * Solution to assignement 6 from exam: TDDD38-220113
 */


// A few test objects
template<class T>
struct A
{
    void operator() (T elem) {
        std::cout
            << "UniCallable( "
            << elem << " )"
            << std::endl;
    }
};

template<class T>
struct B
{
    void operator() (T elem, size_t index) {
        std::cout
            << "DuoCallable( "
            << elem << ", "
            << index << " )" << std::endl;
    }
};

template<class T>
struct C
{
    void operator() (T elem, size_t index, size_t size) {
        std::cout
            << "TriCallable( "
            << elem     << ", "
            << index    << ", "
            << size     << " )" << std::endl;
    }
    void operator() (T) {
        fputs("ERROR: one-arg function called on three-arg capable object!\n", stderr);
    }
};


int main()
{
    // Passing callable objects with different configurations of
    // operator() to enumerate()
    {
        std::vector arr{3,8,6,3};
        A<int> ao;
        B<int> bo;
        C<int> co;

        enumerate(arr, ao);

        puts("");
        enumerate(arr, bo);

        puts("");
        enumerate(arr, co);
    }
}

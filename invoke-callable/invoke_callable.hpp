#ifndef _INVOKE_CALLABLE
#define _INVOKE_CALLABLE

#include <type_traits>
#include <concepts>

#include <array> // Only for std::size()


/*
 * This file defines the function:
 *      enumerate(
 *          Container container,
 *          Callable callable
 *      )
 * The enumerate function will iterate over all elements in the container
 * calling the callable object with as many arguments as possible:
 *      callable(*it, index, sized)
 *      callable(*it, index)
 *      callable(*it)
 */



/*
 *  Concepts filtering Callable objects by the most arguments
 *  their operator() takes.
 */
template<class Callable, class T>
concept TriArg =
        requires(Callable c, T t, std::size_t n) {
            c(t, n, n);
        };

template<class Callable, class T>
concept DuoArg =
        !TriArg<Callable, T>
    &&  requires(Callable c, T t, std::size_t n) {
            c(t, n);
        };

template<class Callable, class T>
concept UniArg =
        !TriArg<Callable, T>
    &&  !DuoArg<Callable, T>
    &&  requires(Callable c, T t) {
            c(t);
        };


/*
 *  Functions invoking Callable with actual arguments.
 *  Constrained by the n-argument Concepts above.
 */
template<class Callable, class T>
typename std::enable_if< TriArg<Callable, T>, void>::type
    invoke_on_callable(Callable c, T elem, std::size_t index, std::size_t size)
{
    c(elem, index, size);
}

template<class Callable, class T>
typename std::enable_if< DuoArg<Callable, T>, void >::type
    invoke_on_callable(Callable c, T elem, std::size_t index, std::size_t)
{
    c(elem, index);
}

template<class Callable, class T>
typename std::enable_if< UniArg<Callable, T>, void >::type
    invoke_on_callable(Callable c, T elem, std::size_t, std::size_t)
{
    c(elem);
}



/*
 * enumerate()
 */
template<class Container, class Callable>
void enumerate(Container const& container, Callable callable)
{
    std::size_t i{0};
    std::size_t size{ std::size(container) };

    for (auto item : container) {
        invoke_on_callable(callable, item, i++, size);
    }
}

#endif

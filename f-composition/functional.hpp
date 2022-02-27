#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H


#include <iostream>
#include <vector>
#include <utility>

/*
 * Composition of functions through operator*
 *
 * Immediate evaluation of <lambda> * <rvalue>
 */
template<typename F, typename G>
auto composition_h(F&& f, G&& g, std::true_type) {
#if DEBUG==1
    std::cout << "<Lambda> * <Lambda> -> <Lambda>" << std::endl; // DEBLURG
#endif
    return [f, g](auto&& t){
        return f( g( std::forward<decltype(t)>(t) ) );
    };
}

template<typename F, typename G>
auto composition_h(F&& f, G&& g, std::false_type) {
#if DEBUG==1
    std::cout << "<Lambda> * T -> T" << std::endl; // DEBLURG
#endif
    return f( g );
}

template<typename F, typename G>
auto operator*(F&& f, G&& g) {
#if DEBUG==1
    std::cout << "f * g -> ";
#endif
    return composition_h(f, g, std::is_lvalue_reference<G&&>());
}


/*
 * Following templates handle mapping of transforming function
 * onto vector<T> types
 */
template<typename Transform, typename T>
auto operator*(Transform&& transform, std::vector<T> const& vec) {
#if DEBUG==1
    std::cout << "<Lambda> * vec<T> -> vec<T> \t[const]" << std::endl; // DEBLURG
#endif
    std::vector<T> transformed_vec;
    transformed_vec.reserve( vec.size() );

    for (auto const& v : vec) {
        transformed_vec.push_back( transform(v) );
    }

    return transformed_vec;
}

template<typename Transform, typename T>
auto operator*(Transform&& transform, std::vector<T>&& vec) {
#if DEBUG==1
    std::cout << "<Lambda> * vec<T> -> vec<T> \t[rvalue]" << std::endl; // DEBLURG
#endif
    std::vector<T> transformed_vec;
    transformed_vec.reserve( vec.size() );

    for (auto const& v : vec) {
        transformed_vec.push_back( transform(v) );
    }

    return transformed_vec;
}

template<typename Transform, typename T>
auto operator*(Transform&& transform, std::vector<T>& vec) {
#if DEBUG==1
    std::cout << "<Lambda> * vec<T> -> vec<T> \t[non-const]" << std::endl;
#endif

    std::vector<T> transformed_vec;
    transformed_vec.reserve( vec.size() );

    for (auto const& v : vec) {
        transformed_vec.push_back( transform(v) );
    }

    return transformed_vec;
}


auto const id = [](auto&& t) -> decltype(t)&& {
    return std::forward<decltype(t)>(t);
};



/*
 * Maps a transform function onto each element in vector<T>
 *
 * Obsolete
 */
template<typename F, typename T>
auto map = [](F&& transform) {
    return [transform](std::vector<T> const& vec) {
        std::vector<T> transformed_vec;
        transformed_vec.reserve( vec.size() );
        for (auto const& v : vec) {
            transformed_vec.push_back( transform(v) );
        }
        return transformed_vec;
    };
};


#endif

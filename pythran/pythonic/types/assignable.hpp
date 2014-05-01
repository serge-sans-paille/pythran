#ifndef PYTHONIC_TYPES_ASSIGNABLE_HPP
#define PYTHONIC_TYPES_ASSIGNABLE_HPP

#include <type_traits>

namespace pythonic {

    struct dummy {};

    template<class T>
        struct assignable {
            typedef T type;
        };
    template<class T>
        struct assignable<T const&> {
            typedef typename assignable<T>::type type;
        };
    template<class T>
        struct assignable<T &> {
            typedef typename assignable<T>::type type;
        };

    template<class T>
        struct lazy{
            typedef typename assignable<T>::type type;  // very conservative :-)
        };
}

#endif

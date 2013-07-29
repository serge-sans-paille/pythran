#ifndef PYTHONIC_TYPES_ASSIGNABLE_HPP
#define PYTHONIC_TYPES_ASSIGNABLE_HPP

#include <type_traits>

namespace pythonic {

    struct dummy {};

    template<class T>
        struct assignable {
            typedef typename std::remove_cv<typename std::remove_reference<T>::type>::type type;
        };

    template<class T>
        struct lazy{
            typedef typename assignable<T>::type type;  // very conservative :-)
        };
}

#endif

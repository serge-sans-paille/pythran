#ifndef PYTHONIC_TYPES_NUMPYTYPE_HPP
#define PYTHONIC_TYPES_NUMPYTYPE_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace types {

        template<class T, typename EnableDefault = void>
            struct numpy_type {
                typedef decltype(std::declval<T>()()) type;
            };

        template<class T>
            struct numpy_type<T, typename std::enable_if<std::is_fundamental<T>::value>::type> {
               typedef T type;
            };

#define SPECIALIZE_NUMPY_TYPE(TYPE) template<> struct numpy_type<TYPE> { typedef TYPE type; }
        SPECIALIZE_NUMPY_TYPE(std::complex<float>);
        SPECIALIZE_NUMPY_TYPE(std::complex<double>);
#undef SPECIALIZE_NUMPY_TYPE
    }

}

#endif


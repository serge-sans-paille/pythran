#ifndef PYTHONIC_TYPES_NUMPYTYPE_HPP
#define PYTHONIC_TYPES_NUMPYTYPE_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace types {

        template<class T>
            struct numpy_type {
                typedef decltype(std::declval<T>()()) type;
            };
        template<> struct numpy_type<bool> { typedef bool type; };
        template<> struct numpy_type<int> { typedef int type; };
        template<> struct numpy_type<long> { typedef long type; };
        template<> struct numpy_type<double> { typedef double type; };
        template<> struct numpy_type<std::complex<long>> { typedef std::complex<long> type; };
        template<> struct numpy_type<std::complex<double>> { typedef std::complex<double> type; };
    }

}

#endif


#ifndef PYTHONIC_BUILTIN_ROUND_HPP
#define PYTHONIC_BUILTIN_ROUND_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace __builtin__ {
        template <class T>
            double round(T const & v, size_t n=0) {
                T p = std::pow(10,n);
                return std::lround(v * p)/p;
            }
        PROXY(pythonic::__builtin__, round);

    }

}

#endif


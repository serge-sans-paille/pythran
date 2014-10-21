#ifndef PYTHONIC_CMATH_COS_HPP
#define PYTHONIC_CMATH_COS_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        template<class T>
            std::complex<T> cos(std::complex<T> const& v)
            {
                return std::cos(v);
            }

            template<class T>
            std::complex<T> cos(T const& v)
            {
                return std::cos(v);
            }

        PROXY(pythonic::cmath, cos);
    }

}

#endif


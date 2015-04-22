#ifndef PYTHONIC_INCLUDE_MATH_FACTORIAL_HPP
#define PYTHONIC_INCLUDE_MATH_FACTORIAL_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace math {

        template<class T>
            T factorial(T x);

        PROXY_DECL(pythonic::math,factorial);

    }

}

#endif


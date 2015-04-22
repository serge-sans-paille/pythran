#ifndef PYTHONIC_MATH_FACTORIAL_HPP
#define PYTHONIC_MATH_FACTORIAL_HPP

#include "pythran/pythonic/include/math/factorial.hpp"

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace math {

        template<class T>
            T factorial(T x)
            {
                long res = 1;
                for(long i=2;i<=x;i++)
                    res *= i;
                return res;
            }
        PROXY_IMPL(pythonic::math,factorial);

    }

}

#endif


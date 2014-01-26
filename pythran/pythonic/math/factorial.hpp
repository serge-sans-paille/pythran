#ifndef PYTHONIC_MATH_FACTORIAL_HPP
#define PYTHONIC_MATH_FACTORIAL_HPP

#include "pythonic/utils/proxy.hpp"

namespace pythonic {

    namespace math {

        template<class T>
            T factorial(T x)
            {
                T res = 1;
                for(T i=2;i<=x;i++)
                    res *= i;
                return res;
            }
        PROXY(pythonic::math,factorial);

    }

}

#endif


#ifndef PYTHONIC_MATH_FREXP_HPP
#define PYTHONIC_MATH_FREXP_HPP

#include "pythran/pythonic/include/math/frexp.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/tuple.hpp"

#include <cmath>

namespace pythonic {

    namespace math {
        std::tuple<double,long> frexp(double x)
        {
            int exp;
            double sig = std::frexp(x,&exp);
            return std::tuple<double,long>(sig,exp);
        }
        PROXY_IMPL(pythonic::math,frexp);

    }

}

#endif


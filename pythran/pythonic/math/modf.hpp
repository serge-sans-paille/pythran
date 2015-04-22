#ifndef PYTHONIC_MATH_MODF_HPP
#define PYTHONIC_MATH_MODF_HPP

#include "pythran/pythonic/include/math/modf.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/tuple.hpp"

#include <cmath>

namespace pythonic {

    namespace math {

        std::tuple<double,double> modf(double x)
        {
            double i;
            double frac = std::modf(x,&i);
            return std::make_tuple(frac,i);
        }

        PROXY_IMPL(pythonic::math,modf);

    }

}

#endif


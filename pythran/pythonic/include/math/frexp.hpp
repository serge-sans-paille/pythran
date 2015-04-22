#ifndef PYTHONIC_INCLUDE_MATH_FREXP_HPP
#define PYTHONIC_INCLUDE_MATH_FREXP_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/tuple.hpp"

#include <cmath>

namespace pythonic {

    namespace math {
        std::tuple<double,long> frexp(double x);
        PROXY_DECL(pythonic::math,frexp);

    }

}

#endif


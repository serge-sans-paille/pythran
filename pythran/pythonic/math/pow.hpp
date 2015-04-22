#ifndef PYTHONIC_MATH_POW_HPP
#define PYTHONIC_MATH_POW_HPP

#include "pythran/pythonic/include/math/pow.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(pow, std::pow);
        PROXY_IMPL(pythonic::math, pow);
    }

}

#endif


#ifndef PYTHONIC_MATH_SQRT_HPP
#define PYTHONIC_MATH_SQRT_HPP

#include "pythran/pythonic/include/math/sqrt.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(sqrt, std::sqrt);
        PROXY_IMPL(pythonic::math, sqrt);
    }

}

#endif


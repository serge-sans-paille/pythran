#ifndef PYTHONIC_MATH_EXPM1_HPP
#define PYTHONIC_MATH_EXPM1_HPP

#include "pythran/pythonic/include/math/expm1.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(expm1, std::expm1);
        PROXY_IMPL(pythonic::math, expm1);
    }

}

#endif


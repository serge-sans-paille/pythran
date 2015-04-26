#ifndef PYTHONIC_MATH_LGAMMA_HPP
#define PYTHONIC_MATH_LGAMMA_HPP

#include "pythran/pythonic/include/math/lgamma.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(lgamma, std::lgamma);
        PROXY_IMPL(pythonic::math, lgamma);
    }

}

#endif


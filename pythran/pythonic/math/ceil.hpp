#ifndef PYTHONIC_MATH_CEIL_HPP
#define PYTHONIC_MATH_CEIL_HPP

#include "pythran/pythonic/include/math/ceil.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(ceil, std::ceil);
        PROXY_IMPL(pythonic::math, ceil);
    }

}

#endif


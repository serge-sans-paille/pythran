#ifndef PYTHONIC_MATH_COSH_HPP
#define PYTHONIC_MATH_COSH_HPP

#include "pythran/pythonic/include/math/cosh.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(cosh, std::cosh);
        PROXY_IMPL(pythonic::math, cosh);
    }

}

#endif


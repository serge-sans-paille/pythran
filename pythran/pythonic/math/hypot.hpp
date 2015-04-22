#ifndef PYTHONIC_MATH_HYPOT_HPP
#define PYTHONIC_MATH_HYPOT_HPP

#include "pythran/pythonic/include/math/hypot.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(hypot, std::hypot);
        PROXY_IMPL(pythonic::math, hypot);
    }

}

#endif


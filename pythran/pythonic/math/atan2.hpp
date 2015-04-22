#ifndef PYTHONIC_MATH_ATAN2_HPP
#define PYTHONIC_MATH_ATAN2_HPP

#include "pythran/pythonic/include/math/atan2.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(atan2, std::atan2);
        PROXY_IMPL(pythonic::math, atan2);
    }

}

#endif


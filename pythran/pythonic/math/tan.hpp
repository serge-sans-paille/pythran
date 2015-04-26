#ifndef PYTHONIC_MATH_TAN_HPP
#define PYTHONIC_MATH_TAN_HPP

#include "pythran/pythonic/include/math/tan.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(tan, std::tan);
        PROXY_IMPL(pythonic::math, tan);
    }

}

#endif


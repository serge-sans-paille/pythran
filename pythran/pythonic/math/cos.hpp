#ifndef PYTHONIC_MATH_COS_HPP
#define PYTHONIC_MATH_COS_HPP

#include "pythran/pythonic/include/math/cos.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(cos, std::cos);
        PROXY_IMPL(pythonic::math, cos);
    }

}

#endif


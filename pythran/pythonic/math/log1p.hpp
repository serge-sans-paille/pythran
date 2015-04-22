#ifndef PYTHONIC_MATH_LOG1P_HPP
#define PYTHONIC_MATH_LOG1P_HPP

#include "pythran/pythonic/include/math/log1p.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(log1p, std::log1p);
        PROXY_IMPL(pythonic::math, log1p);
    }

}

#endif


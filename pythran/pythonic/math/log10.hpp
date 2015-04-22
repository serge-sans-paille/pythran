#ifndef PYTHONIC_MATH_LOG10_HPP
#define PYTHONIC_MATH_LOG10_HPP

#include "pythran/pythonic/include/math/log10.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(log10, std::log10);
        PROXY_IMPL(pythonic::math, log10);
    }

}

#endif


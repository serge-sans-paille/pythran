#ifndef PYTHONIC_MATH_ATAN_HPP
#define PYTHONIC_MATH_ATAN_HPP

#include "pythran/pythonic/include/math/atan.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(atan, std::atan);
        PROXY_IMPL(pythonic::math, atan);
    }

}

#endif


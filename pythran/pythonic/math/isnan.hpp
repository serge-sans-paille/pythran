#ifndef PYTHONIC_MATH_ISNAN_HPP
#define PYTHONIC_MATH_ISNAN_HPP

#include "pythran/pythonic/include/math/isnan.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(isnan, std::isnan);
        PROXY_IMPL(pythonic::math, isnan);
    }

}

#endif


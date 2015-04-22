#ifndef PYTHONIC_MATH_ATANH_HPP
#define PYTHONIC_MATH_ATANH_HPP

#include "pythran/pythonic/include/math/atanh.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(atanh, std::atanh);
        PROXY_IMPL(pythonic::math, atanh);
    }

}

#endif


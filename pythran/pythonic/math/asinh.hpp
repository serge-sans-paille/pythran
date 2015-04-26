#ifndef PYTHONIC_MATH_ASINH_HPP
#define PYTHONIC_MATH_ASINH_HPP

#include "pythran/pythonic/include/math/asinh.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(asinh, std::asinh);
        PROXY_IMPL(pythonic::math, asinh);
    }

}

#endif


#ifndef PYTHONIC_MATH_FLOOR_HPP
#define PYTHONIC_MATH_FLOOR_HPP

#include "pythran/pythonic/include/math/floor.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(floor, std::floor);
        PROXY_IMPL(pythonic::math, floor);
    }

}

#endif


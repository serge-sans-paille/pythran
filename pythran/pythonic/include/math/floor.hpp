#ifndef PYTHONIC_INCLUDE_MATH_FLOOR_HPP
#define PYTHONIC_INCLUDE_MATH_FLOOR_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS_DECL(floor, std::floor);
        PROXY_DECL(pythonic::math, floor);
    }

}

#endif


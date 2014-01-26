#ifndef PYTHONIC_MATH_FLOOR_HPP
#define PYTHONIC_MATH_FLOOR_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::floor;
        PROXY(pythonic::math, floor);
    }

}

#endif


#ifndef PYTHONIC_MATH_SQRT_HPP
#define PYTHONIC_MATH_SQRT_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::sqrt;
        PROXY(pythonic::math, sqrt);
    }

}

#endif


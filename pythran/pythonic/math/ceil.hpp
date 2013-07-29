#ifndef PYTHONIC_MATH_CEIL_HPP
#define PYTHONIC_MATH_CEIL_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::ceil;
        PROXY(pythonic::math, ceil);
    }

}

#endif


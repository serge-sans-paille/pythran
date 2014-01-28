#ifndef PYTHONIC_MATH_COPYSIGN_HPP
#define PYTHONIC_MATH_COPYSIGN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::copysign;
        PROXY(pythonic::math, copysign);
    }

}

#endif


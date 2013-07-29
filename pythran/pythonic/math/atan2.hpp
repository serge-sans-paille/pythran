#ifndef PYTHONIC_MATH_ATAN2_HPP
#define PYTHONIC_MATH_ATAN2_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::atan2;
        PROXY(pythonic::math, atan2);
    }

}

#endif


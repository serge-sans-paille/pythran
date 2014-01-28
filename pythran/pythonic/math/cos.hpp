#ifndef PYTHONIC_MATH_COS_HPP
#define PYTHONIC_MATH_COS_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::cos;
        PROXY(pythonic::math, cos);
    }

}

#endif


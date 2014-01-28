#ifndef PYTHONIC_MATH_LOG1P_HPP
#define PYTHONIC_MATH_LOG1P_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::log1p;
        PROXY(pythonic::math, log1p);
    }

}

#endif


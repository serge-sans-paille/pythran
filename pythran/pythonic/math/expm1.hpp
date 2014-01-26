#ifndef PYTHONIC_MATH_EXPM1_HPP
#define PYTHONIC_MATH_EXPM1_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::expm1;
        PROXY(pythonic::math, expm1);
    }

}

#endif


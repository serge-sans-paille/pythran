#ifndef PYTHONIC_MATH_EXP_HPP
#define PYTHONIC_MATH_EXP_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::exp;
        PROXY(pythonic::math, exp);
    }

}

#endif


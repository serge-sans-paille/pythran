#ifndef PYTHONIC_MATH_POW_HPP
#define PYTHONIC_MATH_POW_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::pow;
        PROXY(pythonic::math, pow);
    }

}

#endif


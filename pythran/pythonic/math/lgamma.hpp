#ifndef PYTHONIC_MATH_LGAMMA_HPP
#define PYTHONIC_MATH_LGAMMA_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::lgamma;
        PROXY(pythonic::math, lgamma);
    }

}

#endif


#ifndef PYTHONIC_MATH_COSH_HPP
#define PYTHONIC_MATH_COSH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::cosh;
        PROXY(pythonic::math, cosh);
    }

}

#endif


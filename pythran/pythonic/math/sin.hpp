#ifndef PYTHONIC_MATH_SIN_HPP
#define PYTHONIC_MATH_SIN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::sin;
        PROXY(pythonic::math, sin);
    }

}

#endif


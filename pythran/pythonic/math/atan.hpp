#ifndef PYTHONIC_MATH_ATAN_HPP
#define PYTHONIC_MATH_ATAN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::atan;
        PROXY(pythonic::math, atan);
    }

}

#endif


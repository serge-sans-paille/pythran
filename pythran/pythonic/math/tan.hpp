#ifndef PYTHONIC_MATH_TAN_HPP
#define PYTHONIC_MATH_TAN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::tan;
        PROXY(pythonic::math, tan);
    }

}

#endif


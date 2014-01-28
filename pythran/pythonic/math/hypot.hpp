#ifndef PYTHONIC_MATH_HYPOT_HPP
#define PYTHONIC_MATH_HYPOT_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::hypot;
        PROXY(pythonic::math, hypot);
    }

}

#endif


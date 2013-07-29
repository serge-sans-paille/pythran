#ifndef PYTHONIC_MATH_ACOS_HPP
#define PYTHONIC_MATH_ACOS_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::acos;
        PROXY(pythonic::math, acos);
    }

}

#endif


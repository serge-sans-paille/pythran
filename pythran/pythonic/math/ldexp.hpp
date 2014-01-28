#ifndef PYTHONIC_MATH_LDEXP_HPP
#define PYTHONIC_MATH_LDEXP_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::ldexp;
        PROXY(pythonic::math, ldexp);
    }

}

#endif


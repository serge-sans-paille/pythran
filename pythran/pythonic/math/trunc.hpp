#ifndef PYTHONIC_MATH_TRUNC_HPP
#define PYTHONIC_MATH_TRUNC_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::trunc;
        PROXY(pythonic::math, trunc);
    }

}

#endif


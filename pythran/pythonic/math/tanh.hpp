#ifndef PYTHONIC_MATH_TANH_HPP
#define PYTHONIC_MATH_TANH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::tanh;
        PROXY(pythonic::math, tanh);
    }

}

#endif


#ifndef PYTHONIC_MATH_LOG10_HPP
#define PYTHONIC_MATH_LOG10_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::log10;
        PROXY(pythonic::math, log10);
    }

}

#endif


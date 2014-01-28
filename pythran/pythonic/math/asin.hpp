#ifndef PYTHONIC_MATH_ASIN_HPP
#define PYTHONIC_MATH_ASIN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::asin;
        PROXY(pythonic::math, asin);
    }

}

#endif


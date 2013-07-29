#ifndef PYTHONIC_MATH_ISNAN_HPP
#define PYTHONIC_MATH_ISNAN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::isnan;
        PROXY(pythonic::math, isnan);
    }

}

#endif


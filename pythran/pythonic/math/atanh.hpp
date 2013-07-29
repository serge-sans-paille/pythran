#ifndef PYTHONIC_MATH_ATANH_HPP
#define PYTHONIC_MATH_ATANH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::atanh;
        PROXY(pythonic::math, atanh);
    }

}

#endif


#ifndef PYTHONIC_MATH_FABS_HPP
#define PYTHONIC_MATH_FABS_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::fabs;
        PROXY(pythonic::math, fabs);
    }

}

#endif


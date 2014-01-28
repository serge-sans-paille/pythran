#ifndef PYTHONIC_MATH_SINH_HPP
#define PYTHONIC_MATH_SINH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::sinh;
        PROXY(pythonic::math, sinh);
    }

}

#endif


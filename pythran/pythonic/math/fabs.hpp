#ifndef PYTHONIC_MATH_FABS_HPP
#define PYTHONIC_MATH_FABS_HPP

#include "pythran/pythonic/include/math/fabs.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(fabs, std::fabs);
        PROXY_IMPL(pythonic::math, fabs);
    }

}

#endif


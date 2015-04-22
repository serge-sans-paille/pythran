#ifndef PYTHONIC_MATH_ACOS_HPP
#define PYTHONIC_MATH_ACOS_HPP

#include "pythran/pythonic/include/math/acos.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(acos, std::acos);
        PROXY_IMPL(pythonic::math, acos);
    }

}

#endif


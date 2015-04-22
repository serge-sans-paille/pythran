#ifndef PYTHONIC_MATH_COPYSIGN_HPP
#define PYTHONIC_MATH_COPYSIGN_HPP

#include "pythran/pythonic/include/math/copysign.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(copysign, std::copysign);
        PROXY_IMPL(pythonic::math, copysign);
    }

}

#endif


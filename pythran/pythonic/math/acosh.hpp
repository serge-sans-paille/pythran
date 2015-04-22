#ifndef PYTHONIC_MATH_ACOSH_HPP
#define PYTHONIC_MATH_ACOSH_HPP

#include "pythran/pythonic/include/math/acosh.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(acosh, std::acosh);
        PROXY_IMPL(pythonic::math, acosh);
    }

}

#endif


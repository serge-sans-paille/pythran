#ifndef PYTHONIC_MATH_SINH_HPP
#define PYTHONIC_MATH_SINH_HPP

#include "pythran/pythonic/include/math/sinh.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(sinh, std::sinh);
        PROXY_IMPL(pythonic::math, sinh);
    }

}

#endif


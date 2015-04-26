#ifndef PYTHONIC_MATH_TRUNC_HPP
#define PYTHONIC_MATH_TRUNC_HPP

#include "pythran/pythonic/include/math/trunc.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(trunc, std::trunc);
        PROXY_IMPL(pythonic::math, trunc);
    }

}

#endif


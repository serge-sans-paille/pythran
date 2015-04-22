#ifndef PYTHONIC_MATH_EXP_HPP
#define PYTHONIC_MATH_EXP_HPP

#include "pythran/pythonic/include/math/exp.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(exp, std::exp);
        PROXY_IMPL(pythonic::math, exp);
    }

}

#endif


#ifndef PYTHONIC_MATH_ERF_HPP
#define PYTHONIC_MATH_ERF_HPP

#include "pythran/pythonic/include/math/erf.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(erf, std::erf);
        PROXY_IMPL(pythonic::math, erf);
    }

}

#endif


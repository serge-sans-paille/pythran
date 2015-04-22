#ifndef PYTHONIC_MATH_ASIN_HPP
#define PYTHONIC_MATH_ASIN_HPP

#include "pythran/pythonic/include/math/asin.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(asin, std::asin);
        PROXY_IMPL(pythonic::math, asin);
    }

}

#endif


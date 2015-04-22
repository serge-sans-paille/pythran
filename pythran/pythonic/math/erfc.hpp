#ifndef PYTHONIC_MATH_ERFC_HPP
#define PYTHONIC_MATH_ERFC_HPP

#include "pythran/pythonic/include/math/erfc.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(erfc, std::erfc);
        PROXY_IMPL(pythonic::math, erfc);
    }

}

#endif


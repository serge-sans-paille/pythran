#ifndef PYTHONIC_MATH_ISINF_HPP
#define PYTHONIC_MATH_ISINF_HPP

#include "pythran/pythonic/include/math/isinf.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(isinf, std::isinf);
        PROXY_IMPL(pythonic::math, isinf);
    }

}

#endif


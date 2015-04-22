#ifndef PYTHONIC_MATH_LDEXP_HPP
#define PYTHONIC_MATH_LDEXP_HPP

#include "pythran/pythonic/include/math/ldexp.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(ldexp, std::ldexp);
        PROXY_IMPL(pythonic::math, ldexp);
    }

}

#endif


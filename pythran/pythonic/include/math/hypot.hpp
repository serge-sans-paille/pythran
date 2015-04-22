#ifndef PYTHONIC_INCLUDE_MATH_HYPOT_HPP
#define PYTHONIC_INCLUDE_MATH_HYPOT_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS_DECL(hypot, std::hypot);
        PROXY_DECL(pythonic::math, hypot);
    }

}

#endif


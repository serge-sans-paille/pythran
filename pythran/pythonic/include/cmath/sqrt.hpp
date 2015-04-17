#ifndef PYTHONIC_INCLUDE_CMATH_SQRT_HPP
#define PYTHONIC_INCLUDE_CMATH_SQRT_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(sqrt ,std::sqrt);
        PROXY_DECL(pythonic::cmath, sqrt);
    }

}

#endif


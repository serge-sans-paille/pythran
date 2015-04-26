#ifndef PYTHONIC_INCLUDE_CMATH_COSH_HPP
#define PYTHONIC_INCLUDE_CMATH_COSH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(cosh, std::cosh);
        PROXY_DECL(pythonic::cmath, cosh);
    }

}

#endif


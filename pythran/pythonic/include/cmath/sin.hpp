#ifndef PYTHONIC_INCLUDE_CMATH_SIN_HPP
#define PYTHONIC_INCLUDE_CMATH_SIN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(sin ,std::sin);
        PROXY_DECL(pythonic::cmath, sin);
    }

}

#endif


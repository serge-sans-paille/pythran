#ifndef PYTHONIC_INCLUDE_CMATH_TAN_HPP
#define PYTHONIC_INCLUDE_CMATH_TAN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(tan, std::tan);
        PROXY_DECL(pythonic::cmath, tan);
    }

}

#endif


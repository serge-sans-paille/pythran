#ifndef PYTHONIC_INCLUDE_CMATH_ATAN_HPP
#define PYTHONIC_INCLUDE_CMATH_ATAN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(atan, std::atan);
        PROXY_DECL(pythonic::cmath, atan);
    }

}

#endif


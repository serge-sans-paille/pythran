#ifndef PYTHONIC_INCLUDE_CMATH_ACOS_HPP
#define PYTHONIC_INCLUDE_CMATH_ACOS_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(acos ,std::acos);
        PROXY_DECL(pythonic::cmath, acos);
    }

}

#endif


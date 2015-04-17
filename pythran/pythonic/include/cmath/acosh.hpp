#ifndef PYTHONIC_INCLUDE_CMATH_ACOSH_HPP
#define PYTHONIC_INCLUDE_CMATH_ACOSH_HPP

#include "pythonic/utils/proxy.hpp"

#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(acosh, std::acosh);
        PROXY_DECL(pythonic::cmath, acosh);
    }

}

#endif


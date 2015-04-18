#ifndef PYTHONIC_CMATH_ACOSH_HPP
#define PYTHONIC_CMATH_ACOSH_HPP

#include "pythonic/include/cmath/acosh.hpp"
#include "pythonic/utils/proxy.hpp"

#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS(acosh, std::acosh);
        PROXY_IMPL(pythonic::cmath, acosh);
    }

}

#endif


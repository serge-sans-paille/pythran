#ifndef PYTHONIC_INCLUDE_CMATH_ASIN_HPP
#define PYTHONIC_INCLUDE_CMATH_ASIN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(asin, std::asin);
        PROXY_DECL(pythonic::cmath, asin);
    }

}

#endif


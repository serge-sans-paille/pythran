#ifndef PYTHONIC_INCLUDE_CMATH_SINH_HPP
#define PYTHONIC_INCLUDE_CMATH_SINH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(sinh, std::sinh);
        PROXY_DECL(pythonic::cmath, sinh);
    }

}

#endif


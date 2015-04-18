#ifndef PYTHONIC_INCLUDE_CMATH_EXP_HPP
#define PYTHONIC_INCLUDE_CMATH_EXP_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(exp ,std::exp);
        PROXY_DECL(pythonic::cmath, exp);
    }

}

#endif


#ifndef PYTHONIC_INCLUDE_CMATH_ASINH_HPP
#define PYTHONIC_INCLUDE_CMATH_ASINH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(asinh ,std::asinh);
        PROXY_DECL(pythonic::cmath, asinh);
    }

}

#endif


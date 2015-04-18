#ifndef PYTHONIC_INCLUDE_CMATH_ISINF_HPP
#define PYTHONIC_INCLUDE_CMATH_ISINF_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS_DECL(isinf ,std::isinf);
        PROXY_DECL(pythonic::cmath, isinf);
    }

}

#endif


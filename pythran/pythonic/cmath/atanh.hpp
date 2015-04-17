#ifndef PYTHONIC_CMATH_ATANH_HPP
#define PYTHONIC_CMATH_ATANH_HPP

#include "pythonic/include/cmath/atanh.hpp"
#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        ALIAS(atanh, std::atanh);
        PROXY_IMPL(pythonic::cmath, atanh);
    }

}

#endif


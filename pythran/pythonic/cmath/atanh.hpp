#ifndef PYTHONIC_CMATH_ATANH_HPP
#define PYTHONIC_CMATH_ATANH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::atanh;
        PROXY(pythonic::cmath, atanh);
    }

}

#endif


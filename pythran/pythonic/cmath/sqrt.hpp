#ifndef PYTHONIC_CMATH_SQRT_HPP
#define PYTHONIC_CMATH_SQRT_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::sqrt;
        PROXY(pythonic::cmath, sqrt);
    }

}

#endif


#ifndef PYTHONIC_CMATH_COSH_HPP
#define PYTHONIC_CMATH_COSH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::cosh;
        PROXY(pythonic::cmath, cosh);
    }

}

#endif


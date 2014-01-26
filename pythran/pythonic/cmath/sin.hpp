#ifndef PYTHONIC_CMATH_SIN_HPP
#define PYTHONIC_CMATH_SIN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::sin;
        PROXY(pythonic::cmath, sin);
    }

}

#endif


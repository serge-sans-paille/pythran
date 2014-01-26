#ifndef PYTHONIC_CMATH_LOG10_HPP
#define PYTHONIC_CMATH_LOG10_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::log10;
        PROXY(pythonic::cmath, log10);
    }

}

#endif


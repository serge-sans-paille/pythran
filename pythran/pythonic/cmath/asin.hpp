#ifndef PYTHONIC_CMATH_ASIN_HPP
#define PYTHONIC_CMATH_ASIN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::asin;
        PROXY(pythonic::cmath, asin);
    }

}

#endif


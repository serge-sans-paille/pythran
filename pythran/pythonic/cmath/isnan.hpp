#ifndef PYTHONIC_CMATH_ISNAN_HPP
#define PYTHONIC_CMATH_ISNAN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::isnan;
        PROXY(pythonic::cmath, isnan);
    }

}

#endif


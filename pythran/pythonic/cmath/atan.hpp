#ifndef PYTHONIC_CMATH_ATAN_HPP
#define PYTHONIC_CMATH_ATAN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::atan;
        PROXY(pythonic::cmath, atan);
    }

}

#endif


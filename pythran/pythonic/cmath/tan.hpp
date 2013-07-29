#ifndef PYTHONIC_CMATH_TAN_HPP
#define PYTHONIC_CMATH_TAN_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::tan;
        PROXY(pythonic::cmath, tan);
    }

}

#endif


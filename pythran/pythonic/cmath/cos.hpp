#ifndef PYTHONIC_CMATH_COS_HPP
#define PYTHONIC_CMATH_COS_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::cos;
        PROXY(pythonic::cmath, cos);
    }

}

#endif


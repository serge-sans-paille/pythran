#ifndef PYTHONIC_CMATH_EXP_HPP
#define PYTHONIC_CMATH_EXP_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::exp;
        PROXY(pythonic::cmath, exp);
    }

}

#endif


#ifndef PYTHONIC_CMATH_ACOS_HPP
#define PYTHONIC_CMATH_ACOS_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::acos;
        PROXY(pythonic::cmath, acos);
    }

}

#endif


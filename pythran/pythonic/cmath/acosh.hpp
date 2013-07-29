#ifndef PYTHONIC_CMATH_ACOSH_HPP
#define PYTHONIC_CMATH_ACOSH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::acosh;
        PROXY(pythonic::cmath, acosh);
    }

}

#endif


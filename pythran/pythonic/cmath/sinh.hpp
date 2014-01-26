#ifndef PYTHONIC_CMATH_SINH_HPP
#define PYTHONIC_CMATH_SINH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::sinh;
        PROXY(pythonic::cmath, sinh);
    }

}

#endif


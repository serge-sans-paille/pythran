#ifndef PYTHONIC_CMATH_TANH_HPP
#define PYTHONIC_CMATH_TANH_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::tanh;
        PROXY(pythonic::cmath, tanh);
    }

}

#endif


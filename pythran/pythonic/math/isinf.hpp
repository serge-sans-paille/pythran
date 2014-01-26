#ifndef PYTHONIC_MATH_ISINF_HPP
#define PYTHONIC_MATH_ISINF_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::isinf;
        PROXY(pythonic::math, isinf);
    }

}

#endif


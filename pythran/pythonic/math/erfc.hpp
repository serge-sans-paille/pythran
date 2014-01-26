#ifndef PYTHONIC_MATH_ERFC_HPP
#define PYTHONIC_MATH_ERFC_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::erfc;
        PROXY(pythonic::math, erfc);
    }

}

#endif


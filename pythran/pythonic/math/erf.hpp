#ifndef PYTHONIC_MATH_ERF_HPP
#define PYTHONIC_MATH_ERF_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::erf;
        PROXY(pythonic::math, erf);
    }

}

#endif


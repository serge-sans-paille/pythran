#ifndef PYTHONIC_MATH_TANH_HPP
#define PYTHONIC_MATH_TANH_HPP

#include "pythran/pythonic/include/math/tanh.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(tanh, std::tanh);
        PROXY_IMPL(pythonic::math, tanh);
    }

}

#endif


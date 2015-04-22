#ifndef PYTHONIC_MATH_LOG_HPP
#define PYTHONIC_MATH_LOG_HPP

#include "pythran/pythonic/include/math/log.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(log, std::log);

        double log(double x, double base)
        {
            return log(x)/log(base);
        }

        PROXY_IMPL(pythonic::math, log);
    }

}

#endif


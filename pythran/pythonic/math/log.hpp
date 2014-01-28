#ifndef PYTHONIC_MATH_LOG_HPP
#define PYTHONIC_MATH_LOG_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::log;
        double log(double x, double base) { return log(x)/log(base); }
        PROXY(pythonic::math, log);
    }

}

#endif


#ifndef PYTHONIC_CMATH_LOG_HPP
#define PYTHONIC_CMATH_LOG_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::log;
        double log(double x, double base) { return log(x)/log(base); }
        PROXY(pythonic::cmath, log);
    }

}

#endif


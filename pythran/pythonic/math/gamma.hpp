#ifndef PYTHONIC_MATH_GAMMA_HPP
#define PYTHONIC_MATH_GAMMA_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/utils/wrap.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        WRAP(double,gamma,std::tgamma,double);
        PROXY(pythonic::math, gamma);
    }

}

#endif


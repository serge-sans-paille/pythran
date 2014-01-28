#ifndef PYTHONIC_MATH_RADIANS_HPP
#define PYTHONIC_MATH_RADIANS_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/math/pi.hpp"

namespace pythonic {

    namespace math {
        template<class T>
            double radians(T x) { return (x * 2. * pi) / 360.; }
        PROXY(pythonic::math,radians);

    }

}

#endif


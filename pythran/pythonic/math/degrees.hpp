#ifndef PYTHONIC_MATH_DEGREES_HPP
#define PYTHONIC_MATH_DEGREES_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/math/pi.hpp"

namespace pythonic {

    namespace math {

        template<class T>
            double degrees(T x) { return (x * 360.) / (2. * pi); }
        PROXY(pythonic::math,degrees);

    }

}

#endif


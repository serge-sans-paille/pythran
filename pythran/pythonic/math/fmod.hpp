#ifndef PYTHONIC_MATH_FMOD_HPP
#define PYTHONIC_MATH_FMOD_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        using std::fmod;
        PROXY(pythonic::math, fmod);
    }

}

#endif


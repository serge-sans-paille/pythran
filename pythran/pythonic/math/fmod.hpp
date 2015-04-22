#ifndef PYTHONIC_MATH_FMOD_HPP
#define PYTHONIC_MATH_FMOD_HPP

#include "pythran/pythonic/include/math/fmod.hpp"

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace math {
        ALIAS(fmod, std::fmod);
        PROXY_IMPL(pythonic::math, fmod);
    }

}

#endif


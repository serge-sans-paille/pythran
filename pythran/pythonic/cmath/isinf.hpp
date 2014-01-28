#ifndef PYTHONIC_CMATH_ISINF_HPP
#define PYTHONIC_CMATH_ISINF_HPP

#include "pythonic/utils/proxy.hpp"
#include <cmath>

namespace pythonic {

    namespace cmath {
        using std::isinf;
        PROXY(pythonic::cmath, isinf);
    }

}

#endif


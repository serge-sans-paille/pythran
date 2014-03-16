#ifndef PYTHONIC_NUMPY_LOGSPACE_HPP
#define PYTHONIC_NUMPY_LOGSPACE_HPP

#include "pythonic/numpy/linspace.hpp"
#include "pythonic/numpy/power.hpp"

namespace pythonic {

    namespace numpy {
        auto logspace(double start, double stop, long num=50, bool endpoint = true, double base=10.0)
            -> decltype(proxy::power()(base, proxy::linspace()(start, stop, num, endpoint)))
            {
                return proxy::power()(base, proxy::linspace()(start, stop, num, endpoint));
            }

        PROXY(pythonic::numpy, logspace);

    }

}

#endif


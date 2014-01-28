#ifndef PYTHONIC_NUMPY_LINSPACE_HPP
#define PYTHONIC_NUMPY_LINSPACE_HPP

#include "pythonic/numpy/arange.hpp"

namespace pythonic {

    namespace numpy {
        types::ndarray<double, 1> linspace(double start, double stop, long num=50, bool endpoint = true)
        {
            double step = (stop - start) / (num - (endpoint?1:0)) ;
            return arange(start, stop + (endpoint?step*.5:0), step);
        }

        PROXY(pythonic::numpy, linspace);

    }

}

#endif


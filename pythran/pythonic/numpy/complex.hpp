#ifndef PYTHONIC_NUMPY_COMPLEX_HPP
#define PYTHONIC_NUMPY_COMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

namespace pythonic {

    namespace numpy {

        std::complex<double> complex() {return std::complex<double>();}
        PROXY(pythonic::numpy, complex);

    }

}

#endif


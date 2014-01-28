#ifndef PYTHONIC_NUMPY_COMPLEX64_HPP
#define PYTHONIC_NUMPY_COMPLEX64_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

namespace pythonic {

    namespace numpy {

        std::complex<double> complex64() {return std::complex<double>();}
        PROXY(pythonic::numpy, complex64);

    }

}

#endif


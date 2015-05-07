#ifndef PYTHONIC_INCLUDE_NUMPY_COMPLEX_HPP
#define PYTHONIC_INCLUDE_NUMPY_COMPLEX_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

namespace pythonic {

    namespace numpy {

        std::complex<double> complex();

        PROXY_DECL(pythonic::numpy, complex);

    }

}

#endif

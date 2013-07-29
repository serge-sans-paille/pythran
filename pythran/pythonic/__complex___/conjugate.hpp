#ifndef PYTHONIC_COMPLEX_CONJUGATE_HPP
#define PYTHONIC_COMPLEX_CONJUGATE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/complex.hpp"

namespace pythonic {

    namespace __complex___ {
        template<class T>
            std::complex<T> conjugate(std::complex<T> const &c) {
                return std::conj(c);
            }
        PROXY(pythonic::__complex___, conjugate);

    }

}

#endif


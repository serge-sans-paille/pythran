#ifndef PYTHONIC_NUMPY_ZEROSLIKE_HPP
#define PYTHONIC_NUMPY_ZEROSLIKE_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/numpy/zeros.hpp"

namespace pythonic {

    namespace numpy {

        template<class E>
            auto zeros_like(E const&expr)
            -> decltype(zeros(expr.shape()))
            {
                return zeros(expr.shape());
            }

        PROXY(pythonic::numpy, zeros_like)

    }

}

#endif


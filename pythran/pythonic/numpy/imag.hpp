#ifndef PYTHONIC_NUMPY_IMAG_HPP
#define PYTHONIC_NUMPY_IMAG_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic {

    namespace numpy {
      template<class E>
        auto imag(E&& expr)
        -> decltype(__builtin__::getattr<types::attr::IMAG>(std::forward<E>(expr)))
        {
          return __builtin__::getattr<types::attr::IMAG>(std::forward<E>(expr));
        }

        PROXY(pythonic::numpy, imag);

    }

}

#endif


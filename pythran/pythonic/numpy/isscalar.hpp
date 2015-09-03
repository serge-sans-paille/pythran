#ifndef PYTHONIC_NUMPY_ISSCALAR_HPP
#define PYTHONIC_NUMPY_ISSCALAR_HPP

#include "pythonic/include/numpy/isscalar.hpp"

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/traits.hpp"
#include "pythonic/types/str.hpp"

#include <type_traits>

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    constexpr bool isscalar(E const &)
    {
      return types::is_dtype<E>::value or std::is_same<E, types::str>::value;
    }

    PROXY_IMPL(pythonic::numpy, isscalar);
  }
}

#endif

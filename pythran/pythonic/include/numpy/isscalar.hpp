#ifndef PYTHONIC_INCLUDE_NUMPY_ISSCALAR_HPP
#define PYTHONIC_INCLUDE_NUMPY_ISSCALAR_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/traits.hpp"
#include "pythonic/include/types/str.hpp"

#include <type_traits>

namespace pythonic
{

  namespace numpy
  {

    template <class E>
    constexpr bool isscalar(E const &);

    DECLARE_FUNCTOR(pythonic::numpy, isscalar);
  }
}

#endif

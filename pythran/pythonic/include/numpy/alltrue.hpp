#ifndef PYTHONIC_INCLUDE_NUMPY_ALLTRUE_HPP
#define PYTHONIC_INCLUDE_NUMPY_ALLTRUE_HPP

#include "pythonic/include/numpy/all.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class... Types>
    auto alltrue(Types &&... types)
        -> decltype(all(std::forward<Types>(types)...));

    DECLARE_FUNCTOR(pythonic::numpy, alltrue);
  }
}

#endif

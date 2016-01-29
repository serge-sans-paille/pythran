#ifndef PYTHONIC_INCLUDE_NUMPY_STD_HPP
#define PYTHONIC_INCLUDE_NUMPY_STD_HPP

#include "pythonic/include/numpy/var.hpp"
#include "pythonic/include/numpy/sqrt.hpp"

namespace pythonic
{

  namespace numpy
  {

    template <class... Args>
    auto std_(Args &&... args)
        -> decltype(functor::sqrt{}(var(std::forward<Args>(args)...)));

    DECLARE_FUNCTOR(pythonic::numpy, std_);
  }
}

#endif

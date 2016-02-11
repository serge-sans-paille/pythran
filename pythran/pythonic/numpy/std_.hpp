#ifndef PYTHONIC_NUMPY_STD_HPP
#define PYTHONIC_NUMPY_STD_HPP

#include "pythonic/include/numpy/std_.hpp"
#include "pythonic/numpy/var.hpp"
#include "pythonic/numpy/sqrt.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class... Args>
    auto std_(Args &&... args)
        -> decltype(functor::sqrt{}(var(std::forward<Args>(args)...)))
    {
      return functor::sqrt{}(var(std::forward<Args>(args)...));
    }

    DEFINE_FUNCTOR(pythonic::numpy, std_);
  }
}

#endif

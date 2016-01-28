#ifndef PYTHONIC_INCLUDE_NUMPY_HSTACK_HPP
#define PYTHONIC_INCLUDE_NUMPY_HSTACK_HPP

#include <pythonic/include/numpy/concatenate.hpp>

namespace pythonic
{

  namespace numpy
  {

    template <class ArraySequence>
    auto hstack(ArraySequence &&seq)
        -> decltype(concatenate(std::forward<ArraySequence>(seq), 1));

    DECLARE_FUNCTOR(pythonic::numpy, hstack);
  }
}

#endif

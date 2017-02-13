#ifndef PYTHONIC_INCLUDE_NUMPY_FILL_DIAGONAL_HPP
#define PYTHONIC_INCLUDE_NUMPY_FILL_DIAGONAL_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/NoneType.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class E>
    types::none_type fill_diagonal(E &&, typename std::decay<E>::type::dtype);

    DECLARE_FUNCTOR(pythonic::numpy, fill_diagonal)
  }
}

#endif

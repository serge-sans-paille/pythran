#ifndef PYTHONIC_NUMPY_FILL_DIAGONAL_HPP
#define PYTHONIC_NUMPY_FILL_DIAGONAL_HPP

#include "pythonic/include/numpy/fill_diagonal.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/NoneType.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class E>
  types::none_type fill_diagonal(E &&expr,
                                 typename std::decay<E>::type::dtype fill_value)
  {
    constexpr auto N = std::decay<E>::type::value;
    auto const &shape = expr.shape();
    types::array<long, N> indices;
    for (long i = 0, n = *std::min_element(shape.begin(), shape.end()); i < n;
         ++i) {
      std::fill(indices.begin(), indices.end(), i);
      expr[indices] = fill_value;
    }
    return {};
  }

  DEFINE_FUNCTOR(pythonic::numpy, fill_diagonal)
}
PYTHONIC_NS_END

#endif

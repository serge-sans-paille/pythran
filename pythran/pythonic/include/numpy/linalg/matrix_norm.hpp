#ifndef PYTHONIC_INCLUDE_NUMPY_LINALG_MATRIX_NORM_HPP
#define PYTHONIC_INCLUDE_NUMPY_LINALG_MATRIX_NORM_HPP

#include "pythonic/include/numpy/linalg/norm.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace linalg
  {
    template <class Array, class Ord = types::str>
    auto matrix_norm(Array &&array, bool keep_dims = true, Ord &&ord = "fro")
    {
      assert(keep_dims && "unsupported keep_dims=false");
      return norm(std::forward<Array>(array), std::forward<Ord>(ord));
    }
    DEFINE_FUNCTOR(pythonic::numpy::linalg, matrix_norm);
  } // namespace linalg
} // namespace numpy
PYTHONIC_NS_END

#endif

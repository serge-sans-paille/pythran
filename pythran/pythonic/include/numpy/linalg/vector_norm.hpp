#ifndef PYTHONIC_INCLUDE_NUMPY_LINALG_VECTOR_NORM_HPP
#define PYTHONIC_INCLUDE_NUMPY_LINALG_VECTOR_NORM_HPP

#include "pythonic/include/numpy/linalg/norm.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace linalg
  {
    template <class Array, class Axis = types::none_type, class Ord = double>
    auto vector_norm(Array &&array, Axis &&axis = {}, bool keep_dims = true, Ord &&ord = 2)
    {
      assert(keep_dims && "unsupported keep_dims=false");
      return norm(std::forward<Array>(array), std::forward<Ord>(ord), std::forward<Axis>(axis));
    }
    DEFINE_FUNCTOR(pythonic::numpy::linalg, vector_norm);
  } // namespace linalg
} // namespace numpy
PYTHONIC_NS_END

#endif

#ifndef PYTHONIC_INCLUDE_NUMPY_TRIMZEROS_HPP
#define PYTHONIC_INCLUDE_NUMPY_TRIMZEROS_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/numpy_gexpr.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T>

  types::numpy_gexpr<
      T, typename types::contiguous_slice<long, long>::normalized_type>
  trim_zeros(T const &expr, types::str const &trim = "fb");

  DEFINE_FUNCTOR(pythonic::numpy, trim_zeros)
}
PYTHONIC_NS_END

#endif

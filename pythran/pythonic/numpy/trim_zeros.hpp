#ifndef PYTHONIC_NUMPY_TRIMZEROS_HPP
#define PYTHONIC_NUMPY_TRIMZEROS_HPP

#include "pythonic/include/numpy/trim_zeros.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/numpy_gexpr.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  template <class T>
  types::numpy_gexpr<
      T, typename types::contiguous_slice<long, long>::normalized_type>
  trim_zeros(T const &expr, types::str const &trim)
  {
    static_assert(T::value == 1,
                  "Not implemented : trim_zeroes only works for 1D array");

    long begin = 0;
    long end = expr.flat_size();
    if (trim.find("f") != -1)
      begin = std::find_if(expr.begin(), expr.end(), [](typename T::dtype i) {
        return i != 0;
      }) - expr.begin();
    if (trim.find("b") != -1)
      while (*(expr.begin() + --end) != 0)
        ;
    return make_gexpr(expr, types::contiguous_slice<long, long>(begin, end));
  }
}
PYTHONIC_NS_END

#endif

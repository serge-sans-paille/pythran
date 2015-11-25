#ifndef PYTHONIC_NUMPY_TRIMZEROS_HPP
#define PYTHONIC_NUMPY_TRIMZEROS_HPP

#include "pythonic/include/numpy/trim_zeros.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/numpy_gexpr.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T>
    types::numpy_gexpr<T, types::contiguous_slice>
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
      return make_gexpr(expr, types::contiguous_slice(begin, end));
    }

    DEFINE_FUNCTOR(pythonic::numpy, trim_zeros)
  }
}

#endif

#ifndef PYTHONIC_NUMPY_NDARRAY_TOLIST_HPP
#define PYTHONIC_NUMPY_NDARRAY_TOLIST_HPP

#include "pythonic/include/numpy/ndarray/tolist.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {

    namespace ndarray
    {

      template <class T>
      types::list<T> tolist(types::ndarray<T, 1> const &expr)
      {
        return {expr.fbegin(), expr.fend()};
      }

      template <class T, size_t N>
      typename tolist_type<T, N>::type tolist(types::ndarray<T, N> const &expr)
      {
        typename tolist_type<T, N>::type out(0);
        for (types::ndarray<T, N - 1> const &elts : expr)
          out.push_back(tolist(elts));
        return out;
      }

      NUMPY_EXPR_TO_NDARRAY0_IMPL(tolist);
      DEFINE_FUNCTOR(pythonic::numpy::ndarray, tolist);
    }
  }
}

#endif

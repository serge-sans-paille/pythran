#ifndef PYTHONIC_NUMPY_ARANGE_HPP
#define PYTHONIC_NUMPY_ARANGE_HPP

#include "pythonic/include/numpy/arange.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T, class U, class S, class dtype>
    types::ndarray<typename dtype::type, 1> arange(T begin, U end, S step,
                                                   dtype d)
    {
      using R = typename dtype::type;
      size_t size = std::max(R(0), R(std::ceil((end - begin) / step)));
      types::ndarray<R, 1> a(types::make_tuple((long)size), __builtin__::None);
      if (size) {
        auto prev = a.fbegin(), end = a.fend();
        *prev = begin;
        for (auto iter = prev + 1; iter != end; ++iter) {
          *iter = *prev + step;
          prev = iter;
        }
      }
      return a;
    }

    template <class T>
    types::ndarray<T, 1> arange(T end)
    {
      return arange(T(0), end);
    }

    DEFINE_FUNCTOR(pythonic::numpy, arange);
  }
}

#endif

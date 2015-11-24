#ifndef PYTHONIC_NUMPY_FROMITER_HPP
#define PYTHONIC_NUMPY_FROMITER_HPP

#include "pythonic/include/numpy/fromiter.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class Iterable, class dtype>
    types::ndarray<typename std::remove_cv<typename std::remove_reference<
                       Iterable>::type>::type::value_type,
                   1>
    fromiter(Iterable &&iterable, dtype d, long count)
    {
      using T = typename std::remove_cv<
          typename std::remove_reference<Iterable>::type>::type::value_type;
      if (count < 0) {
        types::list<T> buffer(0);
        std::copy(iterable.begin(), iterable.end(), std::back_inserter(buffer));
        return {buffer};
      } else {
        T *buffer = (T *)malloc(count * sizeof(T));
        std::copy_n(iterable.begin(), count, buffer);
        long shape[1] = {count};
        return {buffer, shape};
      }
    }

    DEFINE_FUNCTOR(pythonic::numpy, fromiter);
  }
}

#endif

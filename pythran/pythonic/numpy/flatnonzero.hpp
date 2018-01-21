#ifndef PYTHONIC_NUMPY_FLATNONZERO_HPP
#define PYTHONIC_NUMPY_FLATNONZERO_HPP

#include "pythonic/include/numpy/flatnonzero.hpp"

#include "pythonic/numpy/asarray.hpp"

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace
  {
    template <class I, class O>
    void _flatnonzero(I begin, I end, O &out, long &i, utils::int_<1>)
    {
      for (; begin != end; ++begin, ++i)
        if (*begin)
          *out++ = i;
    }

    template <class I, class O, size_t N>
    void _flatnonzero(I begin, I end, O &out, long &i, utils::int_<N>)
    {
      for (; begin != end; ++begin)
        _flatnonzero((*begin).begin(), (*begin).end(), out, i,
                     utils::int_<N - 1>());
    }
  }
  template <class E>
  types::ndarray<long, 1> flatnonzero(E const &expr)
  {
    long n = expr.flat_size();
    utils::shared_ref<types::raw_array<long>> buffer(n);
    long *iter = buffer->data;
    long i = 0;
    _flatnonzero(expr.begin(), expr.end(), iter, i, utils::int_<E::value>());
    types::array<long, 1> shape = {iter - buffer->data};
    return types::ndarray<long, 1>(std::move(buffer), shape);
  }

  DEFINE_FUNCTOR(pythonic::numpy, flatnonzero);
}
PYTHONIC_NS_END

#endif

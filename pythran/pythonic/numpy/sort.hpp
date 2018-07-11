#ifndef PYTHONIC_NUMPY_SORT_HPP
#define PYTHONIC_NUMPY_SORT_HPP

#include "pythonic/include/numpy/sort.hpp"

#include <algorithm>

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace
  {

    template <class T>
    struct _comp {
      bool operator()(T const &i, T const &j) const
      {
        return i < j;
      }
    };

    template <class T>
    struct _comp<std::complex<T>> {
      bool operator()(std::complex<T> const &i, std::complex<T> const &j) const
      {
        if (std::real(i) == std::real(j))
          return std::imag(i) < std::imag(j);
        else
          return std::real(i) < std::real(j);
      }
    };
    template <class T, class pS>
    typename std::enable_if<std::tuple_size<pS>::value == 1, void>::type
    _sort(types::ndarray<T, pS> &out, long axis)
    {
      std::sort(out.begin(), out.end(), _comp<T>{});
    }

    template <class T, class pS>
    typename std::enable_if<std::tuple_size<pS>::value != 1, void>::type
    _sort(types::ndarray<T, pS> &out, long axis)
    {
      constexpr auto N = std::tuple_size<pS>::value;
      if (axis < 0)
        axis += N;

      axis = axis % N;
      auto out_shape = sutils::array(out.shape());
      const long step =
          std::accumulate(out_shape.begin() + axis, out_shape.end(), 1L,
                          std::multiplies<long>());
      for (long i = 0; i < out.flat_size() / out_shape[axis] * step;
           i += step) {
        std::vector<T> to_sort;
        T *iter = out.buffer + (i % out.flat_size() + i / out.flat_size());
        while (iter !=
               out.buffer + (i % out.flat_size() + i / out.flat_size()) +
                   step) {
          to_sort.push_back(*iter);
          iter += step / out_shape[axis];
        }
        std::sort(to_sort.begin(), to_sort.end(), _comp<T>{});
        iter = out.buffer + (i % out.flat_size() + i / out.flat_size());
        for (auto val : to_sort) {
          *iter = val;
          iter += step / out_shape[axis];
        }
      }
    }
  }

  template <class E>
  types::ndarray<typename E::dtype, types::array<long, E::value>>
  sort(E const &expr, long axis)
  {
    auto out = expr.copy();
    _sort(out, axis);
    return out;
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(sort);
}
PYTHONIC_NS_END

#endif

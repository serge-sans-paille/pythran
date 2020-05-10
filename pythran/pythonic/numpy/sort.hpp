#ifndef PYTHONIC_NUMPY_SORT_HPP
#define PYTHONIC_NUMPY_SORT_HPP

#include "pythonic/include/numpy/sort.hpp"

#include <algorithm>

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/str.hpp"
#include "pythonic/numpy/array.hpp"

PYTHONIC_NS_BEGIN
namespace numpy
{
  namespace
  {
    struct quicksorter {
      template <class... Args>
      void operator()(Args &&... args)
      {
        std::sort(std::forward<Args>(args)...);
      }
    };
    struct mergesorter {
      template <class It, class Cmp = std::less<typename It::value_type>>
      void operator()(It first, It last, Cmp cmp = Cmp())
      {
        if (last - first > 1) {
          It middle = first + (last - first) / 2;
          operator()(first, middle, cmp);
          operator()(middle, last, cmp);
          std::inplace_merge(first, middle, last, cmp);
        }
      }
    };
    struct heapsorter {
      template <class... Args>
      void operator()(Args &&... args)
      {
        return std::sort_heap(std::forward<Args>(args)...);
      }
    };
    struct stablesorter {
      template <class... Args>
      void operator()(Args &&... args)
      {
        return std::stable_sort(std::forward<Args>(args)...);
      }
    };

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
    template <class T, class pS, class Sorter>
    typename std::enable_if<std::tuple_size<pS>::value == 1, void>::type
    _sort(types::ndarray<T, pS> &out, long axis, Sorter sorter)
    {
      sorter(out.begin(), out.end(), _comp<T>{});
    }

    template <class T, class pS, class Sorter>
    typename std::enable_if<std::tuple_size<pS>::value != 1, void>::type
    _sort(types::ndarray<T, pS> &out, long axis, Sorter sorter)
    {
      constexpr auto N = std::tuple_size<pS>::value;
      if (axis < 0)
        axis += N;

      auto out_shape = sutils::array(out.shape());
      const long step =
          std::accumulate(out_shape.begin() + axis, out_shape.end(), 1L,
                          std::multiplies<long>());
      long const buffer_size = out_shape[axis];
      T *buffer = new T[buffer_size];
      const long stepper = step / out_shape[axis];
      const long n = out.flat_size() / out_shape[axis] * step;
      long ith = 0, nth = 0;
      for (long i = 0; i < n; i += step) {
        T *buffer_iter = buffer;
        T *iter = out.buffer + ith;
        T *iend = iter + step;
        while (iter != iend) {
          *buffer_iter++ = *iter;
          iter += stepper;
        }
        // FIXME: would probably be faster if we had an iterator adaptor instead
        // of
        // these copies.
        sorter(buffer, buffer + buffer_size, _comp<T>{});
        iter = out.buffer + ith;
        buffer_iter = buffer;
        while (iter != iend) {
          *iter = *buffer_iter++;
          iter += stepper;
        }

        ith += step;
        if (ith - nth == out.flat_size()) {
          ++nth;
          ith = nth;
        }
      }
      delete[] buffer;
    }
  }

  template <class E>
  types::ndarray<typename E::dtype, types::array<long, E::value>>
  sort(E const &expr, long axis)
  {
    auto out = functor::array{}(expr);
    _sort(out, axis, quicksorter());
    return out;
  }

  template <class E>
  types::ndarray<typename E::dtype, types::array<long, 1>>
  sort(E const &expr, types::none_type)
  {
    auto out = functor::array{}(expr).flat();
    _sort(out, 0, quicksorter());
    return out;
  }

  template <class E>
  types::ndarray<typename E::dtype, types::array<long, E::value>>
  sort(E const &expr, long axis, types::str const &kind)
  {
    auto out = functor::array{}(expr);
    if (kind == "quicksort")
      _sort(out, axis, quicksorter());
    else if (kind == "mergesort")
      _sort(out, axis, mergesorter());
    else if (kind == "heapsort")
      _sort(out, axis, heapsorter());
    else if (kind == "stable")
      _sort(out, axis, stablesorter());
    return out;
  }

  NUMPY_EXPR_TO_NDARRAY0_IMPL(sort);
}
PYTHONIC_NS_END

#endif

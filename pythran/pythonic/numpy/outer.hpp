#ifndef PYTHONIC_NUMPY_OUTER_HPP
#define PYTHONIC_NUMPY_OUTER_HPP

#include "pythonic/include/numpy/outer.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/__builtin__/None.hpp"
#include "pythonic/numpy/asarray.hpp"

namespace pythonic
{

  namespace numpy
  {
    template <class T0, size_t N0, class T1, size_t N1>
    types::ndarray<decltype(std::declval<T0>() + std::declval<T1>()), 2>
    outer(types::ndarray<T0, N0> const &a, types::ndarray<T1, N1> const &b)
    {
      types::ndarray<decltype(std::declval<T0>() + std::declval<T1>()), 2> out(
          types::array<long, 2>{{a.flat_size(), b.flat_size()}},
          __builtin__::None);
      auto iter = out.fbegin();
      for (auto iter_a = a.fbegin(), end_a = a.fend(); iter_a != end_a;
           ++iter_a) {
        auto val_a = *iter_a;
        iter = std::transform(b.fbegin(), b.fend(), iter,
                              [=](T1 val) { return val_a * val; });
      }
      return out;
    }

    template <class T0, size_t N0, class E1>
    auto outer(types::ndarray<T0, N0> const &a, E1 const &b)
        -> decltype(outer(a, asarray(b)))
    {
      return outer(a, asarray(b));
    }

    template <class E0, class T1, size_t N1>
    auto outer(E0 const &a, types::ndarray<T1, N1> const &b)
        -> decltype(outer(asarray(a), b))
    {
      return outer(asarray(a), b);
    }

    template <class E0, class E1>
    auto outer(E0 const &a, E1 const &b)
        -> decltype(outer(asarray(a), asarray(b)))
    {
      return outer(asarray(a), asarray(b));
    }

    DEFINE_FUNCTOR(pythonic::numpy, outer);
  }
}

#endif

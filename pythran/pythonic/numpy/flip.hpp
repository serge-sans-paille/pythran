#ifndef PYTHONIC_NUMPY_FLIP_HPP
#define PYTHONIC_NUMPY_FLIP_HPP

#include "pythonic/include/numpy/flip.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_conversion.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace details
    {
      template <class E, class S, int... I>
      auto flip(E const &expr, S const &slices, utils::seq<I...>)
          -> decltype(expr(slices[I]...))
      {
        return expr(slices[I]...);
      }
    }

    template <class E>
    auto flip(E const &expr, long axis)
        -> decltype(details::flip(expr, std::array<types::slice, E::value>{},
                                  typename utils::gens<E::value>::type{}))
    {
      std::array<types::slice, E::value> slices;
      slices[axis].step = -1;
      return details::flip(expr, slices,
                           typename utils::gens<E::value>::type{});
    }
    DEFINE_FUNCTOR(pythonic::numpy, flip);
  }
}

#endif

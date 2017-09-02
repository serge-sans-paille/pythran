#ifndef PYTHONIC_INCLUDE_NUMPY_FLIP_HPP
#define PYTHONIC_INCLUDE_NUMPY_FLIP_HPP

#include "pythonic/include/types/numpy_gexpr.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_conversion.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace details
    {
      template <class E, class S, int... I>
      auto flip(E const &expr, S const &slices, utils::seq<I...>)
          -> decltype(expr(slices[I]...));
    }

    template <class E>
    auto flip(E const &expr, long axis)
        -> decltype(details::flip(expr, std::array<types::slice, E::value>{},
                                  typename utils::gens<E::value>::type{}));

    DECLARE_FUNCTOR(pythonic::numpy, flip);
  }
}

#endif

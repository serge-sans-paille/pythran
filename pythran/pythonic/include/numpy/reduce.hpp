#ifndef PYTHONIC_INCLUDE_NUMPY_REDUCE_HPP
#define PYTHONIC_INCLUDE_NUMPY_REDUCE_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

#ifdef USE_BOOST_SIMD
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/memory/functions/aligned_store.hpp>
#endif

#include <algorithm>

namespace pythonic
{

  namespace numpy
  {

    namespace
    {
      template <class E>
      using reduce_result_type = typename std::conditional<
          std::is_same<typename E::dtype, bool>::value, long,
          typename E::dtype>::type;
    }

    template <class Op, class E>
    typename std::enable_if<types::is_numexpr_arg<E>::value,
                            reduce_result_type<E>>::type
    reduce(E const &expr, types::none_type _ = types::none_type());

    template <class Op, class E>
    typename std::enable_if<
        std::is_scalar<E>::value or types::is_complex<E>::value, E>::type
    reduce(E const &expr, types::none_type _ = types::none_type());

    template <class Op, class E>
    auto reduce(E const &array, long axis) ->
        typename std::enable_if<std::is_scalar<E>::value or
                                    types::is_complex<E>::value,
                                decltype(reduce<Op>(array))>::type;

    template <class Op, class E>
    auto reduce(E const &array, long axis) ->
        typename std::enable_if<E::value == 1,
                                decltype(reduce<Op>(array))>::type;

    namespace
    {
      template <class E>
      using reduced_type = types::ndarray<typename E::dtype, E::value - 1>;
    }

    template <class Op, class E>
    typename std::enable_if<E::value != 1, reduced_type<E>>::type
    reduce(E const &array, long axis);
  }
}

#endif

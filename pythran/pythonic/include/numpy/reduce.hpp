#ifndef PYTHONIC_INCLUDE_NUMPY_REDUCE_HPP
#define PYTHONIC_INCLUDE_NUMPY_REDUCE_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN

namespace numpy
{

  namespace
  {
    template <class E>
    using reduce_result_type = typename std::conditional<
        std::is_integral<typename E::dtype>::value &&
            (sizeof(typename E::dtype) < sizeof(long)),
        typename std::conditional<std::is_signed<typename E::dtype>::value,
                                  long, unsigned long>::type,
        typename E::dtype>::type;
  }

  template <class Op, class E>
  typename std::enable_if<types::is_numexpr_arg<E>::value,
                          reduce_result_type<E>>::type
  reduce(E const &expr, types::none_type _ = types::none_type());

  template <class Op, class E>
  typename std::enable_if<
      std::is_scalar<E>::value || types::is_complex<E>::value, E>::type
  reduce(E const &expr, types::none_type _ = types::none_type());

  template <class Op, class E>
  auto reduce(E const &array, long axis) ->
      typename std::enable_if<std::is_scalar<E>::value ||
                                  types::is_complex<E>::value,
                              decltype(reduce<Op>(array))>::type;

  template <class Op, class E>
  auto reduce(E const &array, long axis,
              types::none_type dtype = types::none_type(),
              types::none_type out = types::none_type()) ->
      typename std::enable_if<E::value == 1, decltype(reduce<Op>(array))>::type;

  template <class Op, class E, class Out>
  auto reduce(E const &array, long axis, types::none_type dtype, Out &&out) ->
      typename std::enable_if<E::value == 1, decltype(reduce<Op>(array))>::type;

  namespace
  {
    template <class E>
    using reduced_type =
        types::ndarray<reduce_result_type<E>, types::array<long, E::value - 1>>;
  }

  template <class Op, class E>
  typename std::enable_if<E::value != 1, reduced_type<E>>::type
  reduce(E const &array, long axis, types::none_type dtype = types::none_type(),
         types::none_type out = types::none_type());

  template <class Op, class E, class Out>
  typename std::enable_if<E::value != 1, reduced_type<E>>::type
  reduce(E const &array, long axis, types::none_type dtype, Out &&out);
}
PYTHONIC_NS_END

#endif

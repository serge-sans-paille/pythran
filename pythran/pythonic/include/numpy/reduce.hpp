#ifndef PYTHONIC_INCLUDE_NUMPY_REDUCE_HPP
#define PYTHONIC_INCLUDE_NUMPY_REDUCE_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/__builtin__/None.hpp"

#include <algorithm>

PYTHONIC_NS_BEGIN
namespace operator_
{
  namespace functor
  {
    struct imax;
    struct imin;
  }
}

namespace numpy
{

  namespace
  {
    template <class Op, class E>
    using reduce_result_type = typename std::conditional<
        std::is_integral<typename E::dtype>::value &&
            (sizeof(typename E::dtype) < sizeof(long)) &&
            !std::is_same<Op, operator_::functor::imin>::value &&
            !std::is_same<Op, operator_::functor::imax>::value,
        typename std::conditional<
            std::is_same<typename E::dtype, bool>::value, long,
            typename std::conditional<std::is_signed<typename E::dtype>::value,
                                      long, unsigned long>::type>::type,
        typename E::dtype>::type;
  }

  template <class Op, class E>
  typename std::enable_if<types::is_numexpr_arg<E>::value,
                          reduce_result_type<Op, E>>::type
  reduce(E const &expr, types::none_type _ = types::none_type());

  template <class Op, class E>
  typename std::enable_if<
      std::is_scalar<E>::value || types::is_complex<E>::value, E>::type
  reduce(E const &expr, types::none_type _ = types::none_type());

  template <class Op, class E>
  typename std::enable_if<
      std::is_scalar<E>::value || types::is_complex<E>::value, E>::type
  reduce(E const &array, long axis);

  template <class Op, class E>
  typename std::enable_if<E::value == 1, reduce_result_type<Op, E>>::type
  reduce(E const &array, long axis, types::none_type dtype = types::none_type(),
         types::none_type out = types::none_type());

  template <class Op, class E, class Out>
  typename std::enable_if<E::value == 1, reduce_result_type<Op, E>>::type
  reduce(E const &array, long axis, types::none_type dtype, Out &&out);

  namespace
  {
    template <class E, class Op>
    using reduced_type = types::ndarray<reduce_result_type<Op, E>,
                                        types::array<long, E::value - 1>>;
  }

  template <class Op, class E>
  typename std::enable_if<E::value != 1, reduced_type<E, Op>>::type
  reduce(E const &array, long axis, types::none_type dtype = types::none_type(),
         types::none_type out = types::none_type());

  template <class Op, class E, class Out>
  typename std::enable_if<E::value != 1, reduced_type<E, Op>>::type
  reduce(E const &array, long axis, types::none_type dtype, Out &&out);
}
PYTHONIC_NS_END

#endif

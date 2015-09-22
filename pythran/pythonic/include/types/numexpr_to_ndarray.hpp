#ifndef PYTHONIC_INCLUDE_TYPES_NUMEXPR_TO_NDARRAY_HPP
#define PYTHONIC_INCLUDE_TYPES_NUMEXPR_TO_NDARRAY_HPP

#include "pythonic/include/utils/nested_container.hpp"

namespace pythonic
{

  namespace types
  {

    template <class T, size_t N>
    struct ndarray;
    template <class T>
    class list;
    template <class T, size_t N>
    struct array;
    template <class T>
    struct is_numexpr_arg;

    /*
             * 3 informations are available:
             * - the type `type` of the equivalent array
             * - the number of dimensions `value` of the equivalent array
             * - the type `T` of the value contained by the equivalent array
             */
    template <class T, class _ = typename std::enable_if<
                           is_numexpr_arg<T>::value,
                           void>::type /* just to filter out scalar types */>
    struct numpy_expr_to_ndarray;

    template <class E, class _>
    struct numpy_expr_to_ndarray {
      using T = typename E::dtype;
      static const size_t N = E::value;
      using type = ndarray<T, N>;
    };

    template <class L, size_t M, class _>
    struct numpy_expr_to_ndarray<array<L, M>, _> {
      using T = typename utils::nested_container_value_type<array<L, M>>::type;
      static const size_t N = utils::nested_container_depth<array<L, M>>::value;
      using type = ndarray<T, N>;
    };

    template <class L, class _>
    struct numpy_expr_to_ndarray<list<L>, _> {
      using T = typename utils::nested_container_value_type<list<L>>::type;
      static const size_t N = utils::nested_container_depth<list<L>>::value;
      using type = ndarray<T, N>;
    };
  }
}
#endif

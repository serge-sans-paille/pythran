#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_SYMMETRICDIFFERENCE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_SYMMETRICDIFFERENCE_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <typename T, typename U>
      typename __combined<types::set<T>, U>::type
      symmetric_difference(types::set<T> const &set, U const &other);

      /* No rvalue overload possible because of return type modification.:
       * >>> a = set([1, 2, 3])
       * >>> b = set([2., 3., 4.])
       * >>> a.symmetric_difference(b)
       * set([1.0, 4.0])
       */

      // combiner is used as other may be list but return is a set
      template <typename U>
      typename __combined<types::empty_set, U>::type
      symmetric_difference(types::empty_set const &set, U const &other);

      DECLARE_FUNCTOR(pythonic::__builtin__::set, symmetric_difference);
    }
  }
}
#endif

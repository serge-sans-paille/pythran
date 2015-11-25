#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_SYMMETRICDIFFERENCEUPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_SYMMETRICDIFFERENCEUPDATE_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/functor.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <typename T, typename U>
      types::none_type symmetric_difference_update(types::set<T> &set,
                                                   U const &other);

      template <typename T, typename U>
      types::none_type symmetric_difference_update(types::set<T> &&set,
                                                   U const &other);

      template <typename U>
      types::none_type symmetric_difference_update(types::empty_set const &set,
                                                   U const &other);

      DECLARE_FUNCTOR(pythonic::__builtin__::set, symmetric_difference_update);
    }
  }
}
#endif

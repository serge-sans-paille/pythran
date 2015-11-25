#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_DIFFERENCEUPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_DIFFERENCEUPDATE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/set.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <typename T, typename... Types>
      types::none_type difference_update(types::set<T> &set,
                                         Types const &... others);

      template <typename T, typename... Types>
      types::none_type difference_update(types::set<T> &&set,
                                         Types const &... others);

      template <typename... Types>
      types::none_type difference_update(types::empty_set const &set,
                                         Types const &... others);

      DECLARE_FUNCTOR(pythonic::__builtin__::set, difference_update);
    }
  }
}
#endif

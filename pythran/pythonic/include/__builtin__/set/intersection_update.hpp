#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_INTERSECTIONUPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_INTERSECTIONUPDATE_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/set.hpp"

namespace pythonic
{

  namespace __builtin__
  {

    namespace set
    {

      template <typename T, typename... Types>
      types::none_type intersection_update(types::set<T> &set,
                                           Types const &... others);

      template <typename T, typename... Types>
      types::none_type intersection_update(types::set<T> &&set,
                                           Types const &... others);

      template <typename... Types>
      types::none_type intersection_update(types::empty_set &&set,
                                           Types const &... others);

      DECLARE_FUNCTOR(pythonic::__builtin__::set, intersection_update);
    }
  }
}
#endif

#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_INTERSECTIONUPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_INTERSECTIONUPDATE_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/set.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      template <typename T, typename... Types>
      void intersection_update(types::set<T> &set, Types const &... others);

      template <typename T, typename... Types>
      void intersection_update(types::set<T> &&set, Types const &... others);

      template <typename... Types>
      void intersection_update(types::empty_set &&set, Types const &... others);

      PROXY_DECL(pythonic::builtins::set, intersection_update);
    }
  }
}
#endif

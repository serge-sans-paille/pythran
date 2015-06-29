#ifndef PYTHONIC_INCLUDE_BUILTIN_SET_SYMMETRICDIFFERENCEUPDATE_HPP
#define PYTHONIC_INCLUDE_BUILTIN_SET_SYMMETRICDIFFERENCEUPDATE_HPP

#include "pythonic/include/types/set.hpp"
#include "pythonic/include/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      template <typename T, typename U>
      void symmetric_difference_update(types::set<T> &set, U const &other);

      template <typename T, typename U>
      void symmetric_difference_update(types::set<T> &&set, U const &other);

      template <typename U>
      void symmetric_difference_update(types::empty_set const &set,
                                       U const &other);

      PROXY_DECL(pythonic::builtins::set, symmetric_difference_update);
    }
  }
}
#endif

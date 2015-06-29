#ifndef PYTHONIC_BUILTIN_SET_SYMMETRICDIFFERENCEUPDATE_HPP
#define PYTHONIC_BUILTIN_SET_SYMMETRICDIFFERENCEUPDATE_HPP

#include "pythonic/include/builtins/set/symmetric_difference_update.hpp"

#include "pythonic/types/set.hpp"
#include "pythonic/utils/proxy.hpp"

namespace pythonic
{

  namespace builtins
  {

    namespace set
    {

      template <typename T, typename U>
      void symmetric_difference_update(types::set<T> &set, U const &other)
      {
        set.symmetric_difference_update(other);
      }

      template <typename T, typename U>
      void symmetric_difference_update(types::set<T> &&set, U const &other)
      {
        // nothing to be done on rvalue
      }

      template <typename U>
      void symmetric_difference_update(types::empty_set const &set,
                                       U const &other)
      {
        // nothing otherwise empty_set have not its correct type.
      }

      PROXY_IMPL(pythonic::builtins::set, symmetric_difference_update);
    }
  }
}
#endif

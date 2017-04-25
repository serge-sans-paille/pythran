#ifndef PYTHONIC_INCLUDE_OS_PATH_JOIN_HPP
#define PYTHONIC_INCLUDE_OS_PATH_JOIN_HPP

#include "pythonic/types/str.hpp"

namespace pythonic
{
  namespace os
  {
    namespace path
    {

      template <class T>
      T join(T &&head);

      template <class T, class... Types>
      types::str join(T &&head, Types &&... tail);

      DECLARE_FUNCTOR(pythonic::os::path, join);
    }
  }
}

#endif

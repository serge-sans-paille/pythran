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
      size_t sizeof_string(T const &s);

      template <class T, class... Types>
      size_t sizeof_string(T const &s, Types &&... tail);

      void _join(types::str &buffer);

      template <class T, class... Types>
      void _join(types::str &buffer, T &&head, Types &&... tail);

      template <class T>
      T join(T &&head);

      template <class T, class... Types>
      types::str join(T &&head, Types &&... tail);

      DECLARE_FUNCTOR(pythonic::os::path, join);
    }
  }
}

#endif

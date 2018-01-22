#ifndef PYTHONIC_INCLUDE_BUILTIN_INT_HPP
#define PYTHONIC_INCLUDE_BUILTIN_INT_HPP

#include "pythonic/include/types/str.hpp"

PYTHONIC_NS_BEGIN

namespace __builtin__
{

  namespace functor
  {

    struct int_ {
      using callable = void;
      using type = long;

      type operator()(char const t[], int base) const;
      type operator()(types::str const &t, int base) const;
      template <class T>
      type operator()(T &&t) const;
      type operator()(char t) const;
      type operator()() const;
    };
  }
}
PYTHONIC_NS_END

#endif

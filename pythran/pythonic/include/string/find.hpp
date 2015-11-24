#ifndef PYTHONIC_INCLUDE_STRING_FIND_HPP
#define PYTHONIC_INCLUDE_STRING_FIND_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace string
  {

    template <class T>
    long find(types::str const &s, T &&val);

    DECLARE_FUNCTOR(pythonic::string, find);
  }
}

#endif

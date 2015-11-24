#ifndef PYTHONIC_STRING_FIND_HPP
#define PYTHONIC_STRING_FIND_HPP

#include "pythonic/include/string/find.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/str.hpp"

namespace pythonic
{

  namespace string
  {

    template <class T>
    long find(types::str const &s, T &&val)
    {
      return s.find(std::forward<T>(val));
    }

    DEFINE_FUNCTOR(pythonic::string, find);
  }
}

#endif

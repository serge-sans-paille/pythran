#ifndef PYTHONIC_INCLUDE_STRING_FIND_HPP
#define PYTHONIC_INCLUDE_STRING_FIND_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/str.hpp"

namespace pythonic
{

  namespace string
  {

    template <class T>
    long find(types::str const &s, T &&val);

    PROXY_DECL(pythonic::string, find);
  }
}

#endif

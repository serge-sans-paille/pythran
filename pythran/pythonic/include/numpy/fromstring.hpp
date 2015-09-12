#ifndef PYTHONIC_INCLUDE_NUMPY_FROMSTRING_HPP
#define PYTHONIC_INCLUDE_NUMPY_FROMSTRING_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/types/list.hpp"

#include <limits>
#include <sstream>

namespace pythonic
{

  namespace numpy
  {
    template <class dtype = double>
    types::ndarray<typename types::numpy_type<dtype>::type, 1>
    fromstring(types::str const &string, dtype d = dtype(), long count = -1,
               types::str const &sep = "");

    PROXY_DECL(pythonic::numpy, fromstring);
  }
}

#endif

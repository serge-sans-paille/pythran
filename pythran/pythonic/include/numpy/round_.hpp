#ifndef PYTHONIC_INCLUDE_NUMPY_ROUND_HPP
#define PYTHONIC_INCLUDE_NUMPY_ROUND_HPP

#include "pythonic/include/utils/proxy.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/include/functions/iround2even.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      T round_(T const &v);
    }

#define NUMPY_NARY_FUNC_NAME round_
#define NUMPY_NARY_FUNC_SYM wrapper::round_
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif

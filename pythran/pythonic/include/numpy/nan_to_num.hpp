#ifndef PYTHONIC_INCLUDE_NUMPY_NANTONUM_HPP
#define PYTHONIC_INCLUDE_NUMPY_NANTONUM_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/numpy/isnan.hpp"

#include <limits>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_positive.hpp>

namespace pythonic
{

  namespace numpy
  {

    namespace wrapper
    {
      template <class I>
      I nan_to_num(I const &a);
    }

#define NUMPY_NARY_FUNC_NAME nan_to_num
#define NUMPY_NARY_FUNC_SYM wrapper::nan_to_num
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif

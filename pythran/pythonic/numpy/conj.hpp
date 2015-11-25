#ifndef PYTHONIC_NUMPY_CONJ_HPP
#define PYTHONIC_NUMPY_CONJ_HPP

#include "pythonic/include/numpy/conj.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/conj.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME conj
#define NUMPY_NARY_FUNC_SYM nt2::conj
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif

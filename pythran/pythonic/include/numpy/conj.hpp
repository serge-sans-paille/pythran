#ifndef PYTHONIC_INCLUDE_NUMPY_CONJ_HPP
#define PYTHONIC_INCLUDE_NUMPY_CONJ_HPP

#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/conj.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME conj
#define NUMPY_NARY_FUNC_SYM nt2::conj
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif

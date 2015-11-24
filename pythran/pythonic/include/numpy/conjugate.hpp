#ifndef PYTHONIC_INCLUDE_NUMPY_CONJUGATE_HPP
#define PYTHONIC_INCLUDE_NUMPY_CONJUGATE_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/conj.hpp>

namespace pythonic
{

  namespace numpy
  {
#define NUMPY_NARY_FUNC_NAME conjugate
#define NUMPY_NARY_FUNC_SYM nt2::conj
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}

#endif

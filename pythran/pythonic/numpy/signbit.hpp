#ifndef PYTHONIC_NUMPY_SIGNBIT_HPP
#define PYTHONIC_NUMPY_SIGNBIT_HPP

#include "pythonic/include/numpy/signbit.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include <nt2/include/functions/bitofsign.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T>
      bool signbit(T const &v)
      {
        return nt2::bitofsign(v);
      }
    }

#define NUMPY_NARY_FUNC_NAME signbit
#define NUMPY_NARY_FUNC_SYM wrapper::signbit
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif

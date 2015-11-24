#ifndef PYTHONIC_NUMPY_LOGADDEXP_HPP
#define PYTHONIC_NUMPY_LOGADDEXP_HPP

#include "pythonic/include/numpy/logaddexp.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/numpy_traits.hpp"
#include "pythonic/types/numpy_broadcast.hpp"

#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>

namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T0, class T1>
      auto logaddexp(T0 const &t0, T1 const &t1)
          -> decltype(nt2::log(nt2::exp(t0) + nt2::exp(t1)))
      {
        return nt2::log(nt2::exp(t0) + nt2::exp(t1));
      }
    }

#define NUMPY_NARY_FUNC_NAME logaddexp
#define NUMPY_NARY_FUNC_SYM wrapper::logaddexp
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif

#ifndef PYTHONIC_NUMPY_LOGADDEXP2_HPP
#define PYTHONIC_NUMPY_LOGADDEXP2_HPP

#include "pythonic/include/numpy/logaddexp2.hpp"

#include "pythonic/utils/functor.hpp"
#include "pythonic/types/ndarray.hpp"
#include "pythonic/types/numpy_broadcast.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include <nt2/include/functions/log2.hpp>
#include <nt2/include/functions/pow.hpp>
namespace pythonic
{

  namespace numpy
  {
    namespace wrapper
    {
      template <class T0, class T1>
      auto logaddexp2(T0 const &t0, T1 const &t1)
          -> decltype(nt2::log2(nt2::pow(T0(2), t0) + nt2::pow(T1(2), t1)))
      {
        return nt2::log2(nt2::pow(T0(2), t0) + nt2::pow(T1(2), t1));
      }
    }

#define NUMPY_NARY_FUNC_NAME logaddexp2
#define NUMPY_NARY_FUNC_SYM wrapper::logaddexp2
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif

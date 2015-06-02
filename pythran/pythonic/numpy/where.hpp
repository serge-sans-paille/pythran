#ifndef PYTHONIC_NUMPY_WHERE_HPP
#define PYTHONIC_NUMPY_WHERE_HPP

#include "pythonic/include/numpy/where.hpp"

#include "pythonic/numpy/asarray.hpp"
#include "pythonic/numpy/nonzero.hpp"
#include "pythonic/numpy/copy.hpp"

namespace pythonic
{

  namespace numpy
  {
    namespace impl
    {
      template <class E, class F, class G>
      typename __combined<F, G>::type where(E const &cond, F const &true_,
                                            G const &false_)
      {
        if (cond)
          return true_;
        else
          return false_;
      }
    }

#define NUMPY_NARY_FUNC_NAME where
#define NUMPY_NARY_FUNC_SYM impl::where
#define NUMPY_NARY_RESHAPE_MODE reshape_type
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}

#endif

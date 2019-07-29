#ifndef PYTHONIC_INCLUDE_SCIPY_SPECIAL_SPH_HARM_HPP
#define PYTHONIC_INCLUDE_SCIPY_SPECIAL_SPH_HARM_HPP

#include "pythonic/include/types/ndarray.hpp"
#include "pythonic/include/utils/functor.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"

PYTHONIC_NS_BEGIN

namespace scipy
{
  namespace special
  {

    namespace details
    {
      template <class T0, class T1>
      std::complex<double> sph_harm(int m, int n, T0 theta, T1 phi);
    }

#define NUMPY_NARY_FUNC_NAME sph_harm
#define NUMPY_NARY_FUNC_SYM details::sph_harm
#include "pythonic/include/types/numpy_nary_expr.hpp"
  }
}
PYTHONIC_NS_END

#endif

#ifndef PYTHONIC_SCIPY_SPECIAL_SPH_HARM_HPP
#define PYTHONIC_SCIPY_SPECIAL_SPH_HARM_HPP

#include "pythonic/include/scipy/special/sph_harm.hpp"

#include "pythonic/types/ndarray.hpp"
#include "pythonic/utils/functor.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#define BOOST_MATH_THREAD_LOCAL thread_local
#include <boost/math/special_functions/spherical_harmonic.hpp>
PYTHONIC_NS_BEGIN

namespace scipy
{
  namespace special
  {
    namespace details
    {
      template <class T>
      double eval_legendre(int n,T x)
      {
        using namespace boost::math::policies;
        return boost::math::legendre_p(n, x,
          make_policy(promote_double<true>()));
      }
    }

#define NUMPY_NARY_FUNC_NAME eval_legendre
#define NUMPY_NARY_FUNC_SYM details::eval_legendre
#include "pythonic/types/numpy_nary_expr.hpp"
  }
}
PYTHONIC_NS_END

#endif

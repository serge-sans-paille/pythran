#ifndef PYTHONIC_INCLUDE_NUMPY_POWER_HPP
#define PYTHONIC_INCLUDE_NUMPY_POWER_HPP

#include "pythonic/include/types/numpy_op_helper.hpp"
#include "pythonic/include/utils/meta.hpp"
#include "pythonic/include/utils/numpy_traits.hpp"
#include "pythonic/include/utils/functor.hpp"

#include <boost/simd/function/pow.hpp>
#ifdef USE_GMP
#include "pythonic/types/long.hpp"
#endif

PYTHONIC_NS_BEGIN

namespace numpy
{
  namespace wrapper
  {
    template <class T0, class T1>
    auto pow(T0 const &t0, T1 const &t1) -> decltype(
        boost::simd::pow((typename std::common_type<T0, T1>::type)t0,
                         (typename std::common_type<T0, T1>::type)t1))
    {
      return boost::simd::pow((typename std::common_type<T0, T1>::type)t0,
                              (typename std::common_type<T0, T1>::type)t1);
    }
    // See https://github.com/MetaScale/nt2/issues/794
    double pow(long const &n, double const &m)
    {
      return pow(static_cast<double>(n), m);
    }
    template <class T>
    std::complex<T> pow(T const &n, std::complex<T> const &m)
    {
      return std::pow(n, m);
    }
    template <class T>
    std::complex<T> pow(std::complex<T> const &n, std::complex<T> const &m)
    {
      return std::pow(n, m);
    }
    template <class T>
    std::complex<T> pow(std::complex<T> const &n, T const &m)
    {
      return std::pow(n, m);
    }
#ifdef USE_GMP
    template <class T0, class U0, class T>
    pythran_long_t pow(__gmp_expr<T0, U0> const &arg0, T const &arg1)
    {
      mpz_class rop;
      mpz_pow_ui(rop.get_mpz_t(), arg0.get_mpz_t(), arg1);
      return rop;
    }
#endif
  }
#define NUMPY_NARY_FUNC_NAME power
#define NUMPY_NARY_FUNC_SYM wrapper::pow
// no need to adapt_type here, as it may turn a**2 into a**2.f
#define NUMPY_NARY_RESHAPE_MODE reshape_type
#include "pythonic/include/types/numpy_nary_expr.hpp"
}
PYTHONIC_NS_END

#endif

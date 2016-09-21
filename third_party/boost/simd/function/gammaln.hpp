//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_GAMMALN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_GAMMALN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-euler
    Function object implementing gammaln capabilities

    Natural logarithm of the absolute value of the Gamma function
     \f$\displaystyle \log |\Gamma(x)|\f$

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = gammaln(x);
    @endcode

    is similar to:

    @code
    T r = log(abs(gamma(x))));
    @endcode

    @par Notes

    - The accuracy of the function is not uniformly good for negative entries
      The algorithm used is currently an adapted vesion of the cephes one.
      For better accuracy in the negative entry case one can use the extern
      boost_math gammaln functor but at a loss of speed.

      However, as stated in boost math:

      "While the relative errors near the positive roots of lgamma are very low,
       the  function has an infinite number of irrational roots for negative arguments:
       very close to these negative roots only a low absolute error can be guaranteed."

    - The call gammaln(x, sgn) also returns the sign of gamma in the output parameter sgn.

       Be aware that POSIX version of lgamma is not thread-safe: each execution of the function
       stores the sign of the gamma function of x in the static external variable signgam.

       boost.simd also provides @ref signgam which independantly computes the sign.

    @par Decorators

    std_ for floating entries  provides access to @c std::lgamma

    @see gamma, signgam

  **/
  Value gammaln(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/gammaln.hpp>
#include <boost/simd/function/simd/gammaln.hpp>

#endif

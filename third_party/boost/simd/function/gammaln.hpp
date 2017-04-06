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
    This function object computes the natural logarithm of the absolute
    value of the Gamma function:
     \f$\displaystyle \log |\Gamma(x)|\f$


    @par Header <boost/simd/function/gammaln.hpp>

    @par Notes

    - The accuracy of the function is not uniformly good for negative entries
      The algorithm used is currently an adapted vesion of the cephes one.
      For better accuracy in the negative entry case, one can use the extern
      boost_math gammaln function but at a loss of speed.

      However, as stated in boost math:

      "While the relative errors near the positive roots of lgamma are very low,
       the  function has an infinite number of irrational roots for negative arguments:
       very close to these negative roots only a low absolute error can be guaranteed."

    - The call `gammaln(x, sgn)` also returns the sign of gamma in the output parameter @c sgn.

       Be aware that POSIX version of @c lgamma is not thread-safe: each execution of the function
       stores the sign of the gamma function of @c x in the static external variable signgam.

       boost.simd also provides @ref signgam which independantly computes the sign.

    @par Decorators

      - std_ fcalls @c std::lgamma

    @see gamma, signgam

    @par Example:

      @snippet gammaln.cpp gammaln

    @par Possible output:

      @snippet gammaln.txt gammaln
  **/
  IEEEValue gammaln(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/gammaln.hpp>
#include <boost/simd/function/simd/gammaln.hpp>

#endif

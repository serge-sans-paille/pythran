//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_STIRLING_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_STIRLING_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-euler
    Function object implementing stirling capabilities

    Computes stirling formula for the gamma function

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = stirling(x);
    @endcode

    Computes  \sqrt{2 \pi} x^{x-\frac12} e^{-x} ( 1 + \frac1{x} P(\frac1{x}))\f$,
    where \f$P\f$ is a polynomial.

    The formula implementation is usable for x between 33 and 172,
    according cephes to approximate \f$\Gamma(x).

    @see gamma, gammaln

  **/
  Value stirling(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/stirling.hpp>
#include <boost/simd/function/simd/stirling.hpp>

#endif

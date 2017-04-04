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
    This function object computes an approwimation of the gamma function
    using the Stirling formula:
  \f$\sqrt{2 \pi} x^{x-\frac12} e^{-x} ( 1 + \frac1{x} P(\frac1{x}))\f$,
    where \f$P\f$ is a polynomial.

    @see gamma, gammaln


    @par Header <boost/simd/function/stirling.hpp>

    @par Example:

      @snippet stirling.cpp stirling

    @par Possible output:

      @snippet stirling.txt stirling

  **/
  Value stirling(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/stirling.hpp>
#include <boost/simd/function/simd/stirling.hpp>

#endif

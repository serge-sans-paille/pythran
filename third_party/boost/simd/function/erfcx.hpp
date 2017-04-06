//==================================================================================================
/*!
  @file
    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ERFCX_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ERFCX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-euler
     This function object computes the  underflow-compensating (scaled) complementary  error function:
   \f$\displaystyle e^{x^2}\frac{2}{\sqrt\pi}\int_{x}^{\infty} e^{-t^2}\mbox{d}t\f$

    @see erfc, erf


    @par Header <boost/simd/function/erfcx.hpp>

    @par Example:

      @snippet erfcx.cpp erfcx

    @par Possible output:

      @snippet erfcx.txt erfcx
  **/
  IEEEValue erfcx(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/erfcx.hpp>
#include <boost/simd/function/simd/erfcx.hpp>

#endif

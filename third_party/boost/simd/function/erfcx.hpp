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
    Function object implementing erfcx capabilities

   Computes the  underflow-compensating (scaled) complementary  error function:
   \f$\displaystyle e^{x^2}\frac{2}{\sqrt\pi}\int_{x}^{\infty} e^{-t^2}\mbox{d}t\f$

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = erfcx(x);
    @endcode

    is similar to:

    @code
    T r = exp(sqr(x))*erfc(x);
    @endcode

    But avoid underflow as much as possible.

    @see erfc, erf

  **/
  Value erfcx(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/erfcx.hpp>
#include <boost/simd/function/simd/erfcx.hpp>

#endif

//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ERFC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ERFC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!
  @ingroup group-euler
    Function object implementing erfc capabilities

  Computes the complementary error function
   \f$\displaystyle \frac{2}{\sqrt\pi}\int_{x}^{\infty} e^{-t^2}\mbox{d}t\f$

  @par Semantic:

  For every parameter of floating type T

  @code
  T r = erfc(x);
  @endcode

  is similar to:

  @code
  T0 r = oneminus(erf(x));
  @endcode

  @par Decorators

  std_ for floating entries provides access to @c std::erfc

  @see erf, erfcx, oneminus

  **/
  Value erfc(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/erfc.hpp>
#include <boost/simd/function/simd/erfc.hpp>

#endif

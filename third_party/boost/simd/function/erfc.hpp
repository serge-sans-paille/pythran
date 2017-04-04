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
   This fFunction object computes the complementary error function
   \f$\displaystyle \frac{2}{\sqrt\pi}\int_{x}^{\infty} e^{-t^2}\mbox{d}t\f$



    @par Header <boost/simd/function/erfc.hpp>

    @par Decorators

   - std_ calls @c std::erfc

    @see erf, erfcx


    @par Example:

      @snippet erfc.cpp erfc

    @par Possible output:

      @snippet erfc.txt erfc
  **/
  IEEEValue erfc(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/erfc.hpp>
#include <boost/simd/function/simd/erfc.hpp>

#endif

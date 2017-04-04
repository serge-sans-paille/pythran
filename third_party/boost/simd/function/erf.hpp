//==================================================================================================
/*!
  @file
    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ERF_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ERF_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-euler
   This function object computes  the error function:
   \f$\displaystyle \frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$


    @par Header <boost/simd/function/erf.hpp>

    @par Decorators

      - std_ calls @c std::erf

    @see erfc,  erfcx

    @par Example:

      @snippet erf.cpp erf

    @par Possible output:

      @snippet erf.txt erf
  **/
  IEEEValue erf(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/erf.hpp>
#include <boost/simd/function/simd/erf.hpp>

#endif

//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOSH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOSH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-hyperbolic
    This function object returns the hyperbolic cosine argument: \f$\log(x+\sqrt{x^2-1})\f$.

    @see cosh, sinh,  acsch, asinh, atanh, asech, acoth, acsch


    @par Header <boost/simd/function/acosh.hpp>

    @par Example:

      @snippet acosh.cpp acosh

    @par Possible output:

      @snippet acosh.txt acosh

  **/
  IEEEValue acosh(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/acosh.hpp>
#include <boost/simd/function/simd/acosh.hpp>

#endif

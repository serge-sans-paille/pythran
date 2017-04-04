//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXPONENTBITS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXPONENTBITS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns the exponent bits of its arguments as an integer value,
    the other bits (sign and mantissa) being just masked.


    @par Header <boost/simd/function/exponentbits.hpp>

    @par Example:

      @snippet exponentbits.cpp exponentbits

    @par Possible output:

      @snippet exponentbits.txt exponentbits

  **/
  as_integer_t<IEEEValue> exponentbits(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/exponentbits.hpp>
#include <boost/simd/function/simd/exponentbits.hpp>

#endif

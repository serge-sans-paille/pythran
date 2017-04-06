//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXPONENT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXPONENT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns the exponent of the floating input.



    @par Header <boost/simd/function/exponent.hpp>

    @par Note:

     The exponent \f$e\f$ and mantissa \f$m\f$ of a floating point entry \f$x\f$ are related by
    \f$x =  m\times 2^e\f$, with  \f$ |m| \in [1, 2[\f$ (except for \f$x = 0\f$,
    where \f$m=0\f$ and \f$e=0\f$ ).

    For integral type inputs exponent is always 0 and mantissa reduces to identity.

    @see mantissa,  frexp, ldexp


    @par Example:

      @snippet exponent.cpp exponent

    @par Possible output:

      @snippet exponent.txt exponent

  **/
  as_integer_t<Value> exponent(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/exponent.hpp>
#include <boost/simd/function/simd/exponent.hpp>

#endif

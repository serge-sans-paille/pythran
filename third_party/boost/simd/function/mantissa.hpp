//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MANTISSA_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MANTISSA_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns the signed mantissa of the input argument.


    @par Header <boost/simd/function/mantissa.hpp>

    @par Note
    The @ref exponent @c e and signed @ref mantissa @c m of a floating
    point entry @c x are related by
    \f$x = m\times 2^e\f$, with |m| \f$\in[1, 2[\f$. (Except for zero,
    for which \f$m = 0\f$).

    @see frexp, pow, exponent


    @par Example:

      @snippet mantissa.cpp mantissa

    @par Possible output:

      @snippet mantissa.txt mantissa

  **/
  Value mantissa(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/mantissa.hpp>
#include <boost/simd/function/simd/mantissa.hpp>

#endif

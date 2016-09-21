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
    Function object implementing mantissa capabilities

    Returns the signed mantissa of the floating input.

    @par Semantic:

    @code
    auto r = mantissa(x);
    @endcode

    is similar to:

    @code
    auto r = x*pow(2, -exponent(x));
    @endcode

    @par Note
    The @ref exponent e and signed @ref mantissa m of a floating point entry a are related by
    \f$a = m\times 2^e\f$, with |m| \f$\in[1, 2[\f$.

    @see frexp, pow, exponent

  **/
  Value mantissa(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/mantissa.hpp>
#include <boost/simd/function/simd/mantissa.hpp>

#endif

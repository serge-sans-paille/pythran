//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SHIFT_LEFT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-operator
    Function object implementing shift_left capabilities

    return left shift of the first operand by the second
    that must be of integer type and of the same number
    of elements as the first parameter

    Infix notation can be used with operator '<<'

    @par Semantic:

    For every parameters of types respectively @c T, @c N:

    @code
    auto r = shift_left(x,n);
    @endcode

    or

    @code
    auto r = x << n;
    @endcode

    @alias shl

    @see  shift_right, shr, rshl, rshr, rol, ror

  **/
  Value shift_left(Value const & x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/shift_left.hpp>
#include <boost/simd/function/simd/shift_left.hpp>

#endif

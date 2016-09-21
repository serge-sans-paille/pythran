//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITWISE_AND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITWISE_AND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing bitwise_and capabilities

    Computes the bitwise and of the two parameters.

    The operands must share the same bit size.

    The result type is the one of the first operand.

    Infix notation can be used with operator '&',
    but this will not work in scalar mode if any
    operand is floating point because of C++ limitations.

    @par Semantic:

    For every parameters of  @c x of type @c T0,  @c y of type @c T1:

    @code
    T0 r = bitwise_and(x,y);
    @endcode

    is similar to:

    @code
    T0 r = x & y;
    @endcode

    @see  bitwise_or, bitwise_xor, bitwise_notand,
    bitwise_andnot, bitwise_notor, bitwise_ornot, complement

  **/
  T0 bitwise_and(T0 const& x, T1 const& y);
} }
#endif

#include <boost/simd/function/scalar/bitwise_and.hpp>
#include <boost/simd/function/simd/bitwise_and.hpp>

#endif

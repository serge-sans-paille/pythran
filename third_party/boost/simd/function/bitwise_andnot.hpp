//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITWISE_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITWISE_ANDNOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing bitwise_andnot capabilities

    Computes the bitwise and not of its parameters.

    The operands must share the same bit size.

    The result type is the one of the first operand.

    @par semantic:
    For any given value @c x, of type @c T0 @c y of type @c T1
    of same memory size:

    @code
    T0 r = bitwise_andnot(x, y);
    @endcode

    The code is equivalent to:

    @code
    T1 r = x & ~y;
    @endcode

    @see  bitwise_and, bitwise_or, bitwise_xor, bitwise_notand,
    bitwise_notor, bitwise_ornot, complement

  **/
  T0 bitwise_andnot(T0 const& x, T1 const& y);
} }
#endif

#include <boost/simd/function/scalar/bitwise_andnot.hpp>
#include <boost/simd/function/simd/bitwise_andnot.hpp>

#endif

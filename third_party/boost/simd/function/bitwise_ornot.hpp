//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITWISE_ORNOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITWISE_ORNOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing bitwise_ornot capabilities

    Computes the bitwise or not of its parameters.

    The operands must share the same bit size.

    The result type is the one of the first operand.

    @par semantic:
    For any given value @c x, of type @c T0, @c y of type @c T1
    of same memory size:

    @code
    T0 r = bitwise_ornot(x, y);
    @endcode

    The code is equivalent to:

    @code
    T0 r = x | ~y;
    @endcode

    @see  bitwise_and, bitwise_xor, bitwise_notand,
    bitwise_andnot, bitwise_notor, bitwise_ornot, complement

  **/
  T0 bitwise_ornot(T0 const &x, T1 const& y);
} }
#endif

#include <boost/simd/function/scalar/bitwise_ornot.hpp>
#include <boost/simd/function/simd/bitwise_ornot.hpp>

#endif

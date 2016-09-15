//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITSET_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITSET_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing bitset capabilities

    Returns x with the ith bit set

    @par semantic:
    For any given value @c x of type @c T, i  of type @c I:

    @code
    T r = bitset(x, i);
    @endcode

    @see  bitget

  **/
  Value bitset(Value const & v0, integer const& i);
} }
#endif

#include <boost/simd/function/scalar/bitset.hpp>
#include <boost/simd/function/simd/bitset.hpp>

#endif

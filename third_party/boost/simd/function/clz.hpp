//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CLZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CLZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing clz capabilities

    Returns  the bit count of leading zeros.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T> r = clz(x);
    @endcode

    @see  ctz, popcnt

  **/
  as_integer_t<Value> clz(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/clz.hpp>
#include <boost/simd/function/simd/clz.hpp>

#endif

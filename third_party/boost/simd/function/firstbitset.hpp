//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FIRSTBITSET_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FIRSTBITSET_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing firstbitset capabilities

    Returns the bit pattern in which the only bit set is
    the first bit set (beginning with the least significant bit) in the parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T,unsigned> r = firstbitset(x);
    @endcode

    @see  ffs,  firstbitunset

  **/
  as_integer_t<Value> firstbitset(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/firstbitset.hpp>
#include <boost/simd/function/simd/firstbitset.hpp>

#endif

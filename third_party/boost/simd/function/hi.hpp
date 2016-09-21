//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_HI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_HI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing hi capabilities

    Returns the high part of the entry
    as an unsigned integer of the size of
    the input.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T,unsigned> r = hi(x);
    @endcode

    @see  lo
  **/
  as_integer_t<Value, unsigned> hi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/hi.hpp>
#include <boost/simd/function/simd/hi.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LO_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LO_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-bitwise
    Function object implementing lo capabilities

    Returns the low part of the entry
    as an unsigned integer of the size of
    the input.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T,unsigned> r = lo(x);
    @endcode

    @see  hi
  **/
  Value lo(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/lo.hpp>
#include <boost/simd/function/simd/lo.hpp>

#endif

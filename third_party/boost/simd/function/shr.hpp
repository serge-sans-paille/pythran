//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SHR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SHR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-operator
    Function object implementing shr capabilities

    Returns the first entry logically shifted right
    by value of the second entry which must be of integtral type.
    If the second entry is negative
    the result is not defined.

    @par semantic:
    For any given value @c x of type @c T,  @c n  of type @c I:

    @code
    auto r = shr(x, n);
    @endcode

    @see  shift_right, shift_left, rshl, rshr, rol, ror

  **/
  Value shr(Value const & x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/shr.hpp>
#include <boost/simd/function/simd/shr.hpp>

#endif

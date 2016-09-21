//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IFLOOR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IFLOOR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing ifloor capabilities

    Computes the integer conversion of the floor of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T> r = ifloor(x);
    @endcode

    is equivalent to:

    @code
    as_integer_t<T> r = saturated_(toint)(floor(x));
    @endcode

    @par Note:
    This operation is properly saturated

  **/
  as_integer_T<Value> ifloor(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/ifloor.hpp>
#include <boost/simd/function/simd/ifloor.hpp>

#endif

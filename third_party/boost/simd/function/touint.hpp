//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TOUINT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TOUINT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing touint capabilities

    Convert to unsigned integer by truncation.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    as_integer_t<T, unsigned> r = touint(x);
    @endcode

    The code is similar to:

    @code
    as_integer_t<T, unsigned> r = static_cast<as_integer_t<T, unsigned> >(x)
    @endcode

    @par Notes:

    @c toint cast a floating value to the unsigned signed integer value of the same bit size.

    This is done by C casting for scalars and corresponding intrinsic in simd (if available).

    Peculiarly,  that implies that the behaviour of this function on invalid or negative
    entries is not defined and possibly unpredictable.

    If you intend to use @ref Nan, @ref Inf or negative entries, consider using @ref saturated_(touint) instead.

    @see toint

  **/
  UIntegerValue toint(Value const & x);
} }
#endif

#include <boost/simd/function/scalar/touint.hpp>
#include <boost/simd/function/simd/touint.hpp>

#endif

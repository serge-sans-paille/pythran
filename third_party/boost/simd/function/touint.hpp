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
    This function object converts its parameter to unsigned integer by truncation.


    @par Header <boost/simd/function/touint.hpp>

    @par Notes

    @c touint cast a floating value to the unsigned signed integer value of the same bit size.

    This is done by C casting for scalars and corresponding intrinsic in simd (if available).

    Peculiarly,  that implies that the behaviour of this function on invalid or negative
    entries is not defined and possibly unpredictable.

    If you intend to use @ref Nan, @ref Inf or negative entries, consider using
    saturated_(touint) instead.


    @par Decorators

    - saturated_ (See @ref group-decorator) as stated above ensures good behaviour on
      limiting values.

    @see toint, tofloat

    @par Example:

      @snippet touint.cpp touint

    @par Possible output:

      @snippet touint.txt touint


  **/
  as_integer_t<Value, unsigned> touint(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/touint.hpp>
#include <boost/simd/function/simd/touint.hpp>

#endif

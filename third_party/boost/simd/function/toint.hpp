//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TOINT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TOINT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object converts its parameter to integer by truncation.


    @par Header <boost/simd/function/toint.hpp>

    @par Notes

    @c toint cast a floating value to the signed integer value of the same bit size.

    This is done by C casting for scalars and corresponding intrinsic in simd (if available).

    Peculiarly,  that implies that the behaviour of this function on invalid entries is
    not defined and quite unpredictable.

    (For instance it is quite frequent that the test: `toint(Inf<double>()) ==  toint(1.0/0.0)`
    will return @ref False whilst the test: `Inf<double>() == 1.0/0.0` returns @ref True !)

    If you intend to use @ref Nan and @ref Inf entries,  consider using
    saturated_(toint) instead or its alias @ref ifix.

    @par Decorators

    - saturated_ (See @ref group-decorator) as stated above ensures good behaviour on
      limiting values.

    @see touint, tofloat

    @par Example:

      @snippet toint.cpp toint

    @par Possible output:

      @snippet toint.txt toint
  **/
  as_integer_t<Value> toint(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/toint.hpp>
#include <boost/simd/function/simd/toint.hpp>

#endif

//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ABS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ABS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-arithmetic
    The function object @c abs computes the absolute value of its parameter.
    If the result cannot be represented by the return type the return is equal to the input.


    @par Header <boost/simd/function/abs.hpp>

    @par Notes

    - Be aware that for signed integers the absolute value of @ref Valmin is
      not representable  in the input type and the result is undefined.

      To avoid this, you may use the `saturated_` decorator (See @ref group-decorator.)

    - @c abs is a also a standard library function name and there possibly exists
    a C macro version which may be called instead of the boost simd version.
    To avoid this you may prefix abs using boost::simd::abs notation.

    @par Decorators

     - `std_`  (See @ref group-decorator) for floating entries results in a call to std::abs,
       in this case the behavior is also undefined if the result cannot be represented by the
       return type.
     - `saturated_` (See @ref group-decorator) garanties that saturated_(abs)(x) will never
       be strictly less than 0. In fact the only change if that for any signed type T
       saturated_(abs)(Valmin<T>()) will be Valmax<T>()) which is already true for
       boost::simd::abs with floating types but not for integral signed types.

    @see sqr_abs, sqr

    @par Example:

      @snippet abs.cpp abs

    @par Possible output:

      @snippet abs.txt abs

  **/
  Value abs(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/abs.hpp>
#include <boost/simd/function/simd/abs.hpp>

#endif

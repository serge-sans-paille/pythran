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
    Function object implementing abs

    Computes the absolute value of its parameter.

    @par Semantic

    For any value @c x of type @c T,

    @code
    T r = abs(x);
    @endcode

    is similar to:

    @code
    T r = x < T(0) ? -x : x;
    @endcode

    @par Notes:

    - Be aware that for signed integers the absolute value of @ref Valmin is
    @ref Valmin (thus negative!). This is a side effect of the 2-complement
    representation of integers. To avoid this, you may use the
    saturated_ @ref decorator or convert the input parameter to a larger type
    before taking the absolute value.

    - abs is a also a standard library function name and there possibly exists
    a C macro version which may be called instead of the boost simd version.
    To avoid this you may prefix abs using boost::simd::abs notation.

    @par Decorators

     - std_ @ref decorator for floating entries results in a call to std::abs
     - saturated_ @ref decorator garanties that saturated_(abs)(x) will never be strictly less than 0.
       In fact the only change if that for any signed type T saturated_(abs)(Valmin<T>()) will be
       Valmax<T>()) which is already true for boost::simd::abs with floating types but not for integral
       signed types.

    @see sqr_abs, sqr

  **/
  Value abs(Value const& a0);
} }
#endif

#include <boost/simd/function/scalar/abs.hpp>
#include <boost/simd/function/simd/abs.hpp>

#endif

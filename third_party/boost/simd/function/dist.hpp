//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DIST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DIST_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the absolute value of the difference of its parameters.

    @par Header <boost/simd/function/dist.hpp>

    @par Notes

    The result may be negative for signed integers as @ref abs(@ref Valmin) is undefined.
    To avoid the problem you can apply to dist the saturated_ decorator (See
    @ref group-decorator.)

    @par Decorators

     - saturated_ garanties that @c saturated_(dist)(x, y)) will
       never be strictly less than 0.

    @see  ulpdist, abs

    @par Example:

      @snippet dist.cpp dist

    @par Possible output:

      @snippet dist.txt dist

  **/
  Value dist(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/dist.hpp>
#include <boost/simd/function/simd/dist.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CLAMP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CLAMP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    This function object clamps @c x between  @c lo and  @c hi.
    If  @c x is less than @c hi, returns the larger of @c x and @c lo, otherwise returns the smaller of @c x and @c hi.


    @par Header <boost/simd/function/clamp.hpp>

    @par Decorators

      - pedantic_ ensures standard  conformity for a Nan first parameter.
      - std_ is not available yet as the stlibc++ version is only defined since C++17.

    @par Example:

       @snippet clamp.cpp clamp

    @par Possible output:

       @snippet clamp.txt clamp

  **/
  Value clamp(Value const& x, Value const& lo, Value const& hi);
} }
#endif

#include <boost/simd/function/scalar/clamp.hpp>
#include <boost/simd/function/simd/clamp.hpp>

#endif

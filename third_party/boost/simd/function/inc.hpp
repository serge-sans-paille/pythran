//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_INC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_INC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-arithmetic
    This function object returns  its parameter incremented by 1.

    @par Header <boost/simd/function/inc.hpp>

    @par Decorators

     - saturated_ ensures that @c saturated_(inc)(x) will never be strictly
     less than @c x, avoiding the wrap around from @ref Valmax to
     @ref Valmin with integer types.

    @see plus, dec, minus

    @par Example:

      @snippet inc.cpp inc

    @par Possible output:

      @snippet inc.txt inc
  **/
  Value inc(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/inc.hpp>
#include <boost/simd/function/simd/inc.hpp>

#endif

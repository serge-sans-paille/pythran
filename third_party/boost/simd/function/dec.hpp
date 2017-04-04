//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-arithmetic
    This function object returns  its parameter decremented by 1.

    @par Header <boost/simd/function/dec.hpp>

    @par Decorators

    - saturated_ ensures that @c saturated_(dec)(x) will never be
      strictly greater than @c x,
      avoiding the wrap around from @ref Valmin to
      @ref Valmax with integer types

    @see inc, minus

    @par Example:

      @snippet dec.cpp dec

    @par Possible output:

      @snippet dec.txt dec
  **/
  Value dec(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/dec.hpp>
#include <boost/simd/function/simd/dec.hpp>

#endif

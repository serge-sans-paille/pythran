//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TOFLOAT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object converts its parameter to floating point value occupying the same bit size.
    This implies that this functor is only defined for (smd vectors of) 32 or 64 bit integer
    entries to provide (smd vectors of) float and or double.

    @see toint, touint, cast


    @par Header <boost/simd/function/tofloat.hpp>

    @par Example:

      @snippet tofloat.cpp tofloat

    @par Possible output:

      @snippet tofloat.txt tofloat
  **/
  as_floating_t<Value> tofloat(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/tofloat.hpp>
#include <boost/simd/function/simd/tofloat.hpp>

#endif

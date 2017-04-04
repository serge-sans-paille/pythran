//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITWISE_CAST_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-bitwise

    This function object function implementing bitwise_cast capabilities

    Performs a bit-preserving cast of its parameters into an arbitrary
    type @c Target.

    @pre `sizeof(Value) == sizeof(Target)`

    @par Header <boost/simd/function/bitwise_cast.hpp>

    @par Example:

      @snippet bitwise_cast.cpp bitwise_cast

    @par Possible output:

      @snippet bitwise_cast.txt bitwise_cast

    @param x Value to cast

    @return A value of type @c Target which is bit-equivalent to @c x.
  **/
  template <typename Target>
  Target bitwise_cast(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/bitwise_cast.hpp>
#include <boost/simd/function/simd/bitwise_cast.hpp>

#endif

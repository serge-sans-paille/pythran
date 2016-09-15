//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

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
      Function object function implementing bitwise_cast capabilities

      Performs a bit-preserving cast of its parameters into an arbitrary
      type @c Target.


      @par Semantic

      For any value @c x of type @c T and for type @c Target,
      of same bit size as T


      @code
      Target r = bitwise_cast<Target>(x);
      @endcode

      @pre
      @code
      sizeof(T) == sizeof(Target)
      @endcode

      @tparam Target @c Target type to cast toward
      @param  @c x Value to cast

      @return A value of type @c Target which is bit-equivalent to @c x.
    **/
    Target bitwise_cast(Value const& x);
  }
} }
#endif

#include <boost/simd/function/scalar/bitwise_cast.hpp>
#include <boost/simd/function/simd/bitwise_cast.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MINF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MINF_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generates the -inf IEEE value (\f$-\infty\f$) for floating types and minimum value
    for integer types

    @par Semantic

    For any type @c T,

    @code
    T x = Minf<T>();
    @endcode


    @return The least value for the input type
  **/
  template<typename T> T Minf();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant

      Generates the -inf IEEE value (\f$-\infty\f$) for floating types and minimum value
      for integer types

      @par Semantic

      For any type @c T,

      @code
      T x = minf(as(T{}));
      @endcode

      return the minimum representable value for this type.

      @return The minimum representable value of the input type
    **/
    Value Minf();
  }
} }
#endif

#include <boost/simd/constant/definition/minf.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INF_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the Inf IEEE value (\f$\infty\f$) for floating types and maximum value
    for integer types

    @par Semantic

    For any type @c T,

    @code
    T x = Inf<T>();
    @endcode

    return IEEE Inf for floating types otherwise the maximum representable value for this type.

    @return The largest value of the input type
  **/
  template<typename T> T Inf();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant

      @return The largest representable value of the input type
    **/
    Value Inf();
  }
} }
#endif

#include <boost/simd/constant/definition/inf.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

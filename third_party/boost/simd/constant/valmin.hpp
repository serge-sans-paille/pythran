//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_VALMIN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_VALMIN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the minimum finite representable value of a given type as a constant.

    @par Semantic

    For any type @c T,

    @code
    T x = Valmin<T>();
    @endcode

    return the minimum finite representable value for this type.

    @return The minimum finite representable value of the input type
  **/
  template<typename T> T Valmin();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant

      Generate the minimum representable value of a given type as a constant.

      @par Semantic

      For any type @c T,

      @code
      T x = valmin(as(T{}));
      @endcode

      return the minimum representable value for this type.

      @return The minimum representable value of the input type
    **/
    Value Valmin();
  }
} }
#endif

#include <boost/simd/constant/definition/valmin.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

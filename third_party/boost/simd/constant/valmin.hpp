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

/*!
  @ingroup group-constant
  @defgroup constant-Valmin Valmin (function template)

  Generates the minimum signed finite representable value of a given type.

  @headerref{<boost/simd/constant/valmin.hpp>}

  @par Description

  1.  @code
      template<typename T> T Valmin();
      @endcode

  2.  @code
      template<typename T> T Valmin( boost::simd::as_<T> const& target );
      @endcode

  Generates the minimum signed finite representable value of a given type.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to:

  - `T(std::numeric_limits<scalar_of_t<T>>::min())` if @c T models IntegerValue
  - `T(-std::numeric_limits<scalar_of_t<T>>::max())` if @c T models IEEEValue

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/valmin.hpp>
#include <boost/simd/constant/simd/valmin.hpp>

#endif

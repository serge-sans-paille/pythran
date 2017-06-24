//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_NAN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_NAN_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Nan Nan (function template)

  Generates the Not a Number (Nan) constant

  @headerref{<boost/simd/constant/nan.hpp>}

  @par Description

  1.  @code
      template<typename T> T Nan();
      @endcode

  2.  @code
      template<typename T> T Nan( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to the Quiet NaN, i.e an IEEE value with all bits
  set to 1.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(std::numeric_limits<scalar_of_t<T>>::quiet_NaN())`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/nan.hpp>
#include <boost/simd/constant/simd/nan.hpp>

#endif

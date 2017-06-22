//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_REAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_REAL_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Real Real (function template)

  Generates a constant from a compile-time IEEE754 bits pattern.

  @headerref{<boost/simd/constant/real.hpp>}

  @par Description

  @code
  template<typename T, std::uintmax_t Double, std::uintmax_t Single> T Real();
  @endcode

  Generates a value of type @c T that evaluates to a IEEE754 value which bits correspond to
  either `Double` or `Single` depending on the type of `scalar_of_t<T>`.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to:
  - `T(bitwise_cast<scalar_of_t<T>>(Double))` if `scalar_of_t<T>` is `double`.
  - `T(bitwise_cast<scalar_of_t<T>>(Single))` if `scalar_of_t<T>` is `float`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/real.hpp>
#include <boost/simd/constant/simd/real.hpp>

#endif

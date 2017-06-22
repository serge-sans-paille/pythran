//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_RATIO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_RATIO_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Ratio Ratio (function template)

  Generates a constant defined by compile-time rational number representation.

  @headerref{<boost/simd/constant/ratio.hpp>}

  @par Description

  @code
  template<typename T,std::uintmax_t Num, std::uintmax_t Denum> T Ratio();
  @endcode

  Generates a value of type @c T that evaluates to `Num/Denum`.

  @par Template Parameters

  | Name           | Description              |
  |---------------:|:-------------------------|
  | **T**          | the constant type        |
  | **Num**        | the constant numerator   |
  | **Denum**      | the constant denumerator |

  @par Return Value
  A value of type @c T that evaluates to `T(Num)/T(Denum)`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/ratio.hpp>
#include <boost/simd/constant/simd/ratio.hpp>

#endif

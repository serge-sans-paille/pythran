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

/*!
  @ingroup group-constant
  @defgroup constant-Inf Inf (function template)

  Generates a constant greater than all other numeric values of a given type.

  @headerref{<boost/simd/constant/inf.hpp>}

  @par Description

  1.  @code
      template<typename T> T Inf();
      @endcode

  2.  @code
      template<typename T> T Inf( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T which value is greater than all other numeric values of type @c T.
  Compared to the [C++ standard infinity](http://en.cppreference.com/w/cpp/types/numeric_limits/infinity),
  `Inf<T>()` is defined for both IEEEValue and IntegerValue.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to:
  - `T(std::numeric_limits<scalar_of_t<T>>::inf()` if @c T models IEEEValue.
  - [the maximum representable value](@ref constant-Valmax) if @c T models IntegerValue.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/inf.hpp>
#include <boost/simd/constant/simd/inf.hpp>

#endif

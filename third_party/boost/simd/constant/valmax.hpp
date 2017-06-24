//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_VALMAX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_VALMAX_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Valmax Valmax (function template)

  Generates the maximum finite representable value of a given type.

  @headerref{<boost/simd/constant/valmax.hpp>}

  @par Description

  1.  @code
      template<typename T> T Valmax();
      @endcode

  2.  @code
      template<typename T> T Valmax( boost::simd::as_<T> const& target );
      @endcode

  Generates the maximum finite representable value of a given type
  [as defined by the C++ standard](http://en.cppreference.com/w/cpp/types/numeric_limits/max).

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(std::numeric_limits<scalar_of_t<T>>::max())`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/valmax.hpp>
#include <boost/simd/constant/simd/valmax.hpp>

#endif

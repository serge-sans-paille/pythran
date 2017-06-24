//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FOUR_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FOUR_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Four Four (function template)

  Generates the constant @c 4.

  @headerref{<boost/simd/constant/four.hpp>}

  @par Description

  1.  @code
      template<typename T> T Four();
      @endcode

  2.  @code
      template<typename T> T Four( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T  that evaluates to 4.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(4)`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/four.hpp>
#include <boost/simd/constant/simd/four.hpp>

#endif

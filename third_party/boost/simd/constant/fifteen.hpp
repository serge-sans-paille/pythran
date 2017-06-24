//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FIFTEEN_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FIFTEEN_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Fifteen Fifteen (function template)

  Generates the constant @c 15.

  @headerref{<boost/simd/constant/fifteen.hpp>}

  @par Description

  1.  @code
      template<typename T> T Fifteen();
      @endcode

  2.  @code
      template<typename T> T Fifteen( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 15.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(15)`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/fifteen.hpp>
#include <boost/simd/constant/simd/fifteen.hpp>

#endif

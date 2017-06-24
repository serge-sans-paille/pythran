//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_THREE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_THREE_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Three Three (function template)

  Generates the constant @c 3

  @headerref{<boost/simd/constant/three.hpp>}

  @par Description

  1.  @code
      template<typename T> T Three();
      @endcode

  2.  @code
      template<typename T> T Three( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 3.


  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(3)`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/three.hpp>
#include <boost/simd/constant/simd/three.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MFIVE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MFIVE_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Mfive Mfive (function template)

  Generates the constant @c -5.

  @headerref{<boost/simd/constant/mfive.hpp>}

  @par Description

  1.  @code
      template<typename T> T Mfive();
      @endcode

  2.  @code
      template<typename T> T Mfive( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to -5.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c that evaluates to `T(-5)`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/mfive.hpp>
#include <boost/simd/constant/simd/mfive.hpp>

#endif

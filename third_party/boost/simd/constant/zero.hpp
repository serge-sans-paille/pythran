//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_ZERO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_ZERO_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Zero Zero (function template)

  Generates the constant @c 0.

  @headerref{<boost/simd/constant/zero.hpp>}

  @par Description

  1.  @code
    template<typename T> T Zero();
    @endcode

  2.  @code
    template<typename T> T Zero( boost::simd::as_<T> const& target );
    @endcode

  Generates a value of type @c T that evaluates to 0.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to <tt>T(0)</tt>.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/zero.hpp>
#include <boost/simd/constant/simd/zero.hpp>

#endif

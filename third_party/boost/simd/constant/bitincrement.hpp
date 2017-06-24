//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_BITINCREMENT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_BITINCREMENT_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Bitincrement Bitincrement (function template)

  Generates the minimal increment constant for a given type.

  @headerref{<boost/simd/constant/bitincrement.hpp>}

  @par Description

  1.  @code
      template<typename T> T Bitincrement();
      @endcode

  2.  @code
      template<typename T> T Bitincrement( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to the minimal increment value for @c T.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that is defined as :

  - the constant `T(1)` if @c T models IntegerValue
  - the constant `next(T(0))` if @c T models IEEEValue

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/bitincrement.hpp>
#include <boost/simd/constant/simd/bitincrement.hpp>

#endif

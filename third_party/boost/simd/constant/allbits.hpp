//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_ALLBITS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Allbits Allbits (function template)

  Generates a constant with all bits set to 1.

  @headerref{<boost/simd/constant/allbits.hpp>}

  @par Description

  1.  @code
      template<typename T> T Allbits();
      @endcode

  2.  @code
      template<typename T> T Allbits( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T with all bits set to 1.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to

  - `Nan<T>()` if @c T models IEEEValue
  - `T(~0)` if @c T models IntegerValue

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/allbits.hpp>
#include <boost/simd/constant/simd/allbits.hpp>

#endif

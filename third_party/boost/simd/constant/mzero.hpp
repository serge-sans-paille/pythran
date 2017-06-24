//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MZERO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MZERO_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Mzero Mzero (function template)

  Generates the constant @c -0.

  @headerref{<boost/simd/constant/mzero.hpp>}

  @par Description

  1.  @code
      template<typename T> T Mzero();
      @endcode

  2.  @code
      template<typename T> T Mzero( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T  that evaluates to -0.

  This constant is the second IEEE representation of 0 and is defined so
  that the expression `1/Mzero<T>() == Minf<T>()` evaluates to @c true. When computed as an
  IntegerValue, the expression `Mzero<T>() == Zero<T>()` evaluates to @c true.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(-0.0)`

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/mzero.hpp>
#include <boost/simd/constant/simd/mzero.hpp>

#endif

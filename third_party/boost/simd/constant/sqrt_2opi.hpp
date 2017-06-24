//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRT_2OPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRT_2OPI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Sqrt_2opi Sqrt_2opi (function template)

  Generates the constant \f$\frac{\sqrt2}{\pi}\f$

  @headerref{<boost/simd/constant/sqrt_2opi.hpp>}

  @par Description

  1.  @code
      template<typename T> T Sqrt_2opi();
      @endcode

  2.  @code
      template<typename T> T Sqrt_2opi( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac{\sqrt2}{\pi}\f$

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.45015815807855303477759959550337)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/sqrt_2opi.hpp>
#include <boost/simd/constant/simd/sqrt_2opi.hpp>

#endif

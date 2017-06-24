//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRT_2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRT_2PI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Sqrt_2pi Sqrt_2pi (function template)

  Generates the constant \f$\sqrt{2\pi}\f$

  @headerref{<boost/simd/constant/sqrt_2pi.hpp>}

  @par Description

  1.  @code
      template<typename T> T Sqrt_2pi();
      @endcode

  2.  @code
      template<typename T> T Sqrt_2pi( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\sqrt{2\pi}\f$.


  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(2.506628274631000502415765284811)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/sqrt_2pi.hpp>
#include <boost/simd/constant/simd/sqrt_2pi.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVSQRT_2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVSQRT_2PI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Invsqrt_2pi Invsqrt_2pi (function template)

  Generates the constant \f$\frac{1}{\sqrt{2\pi}}\f$

  @headerref{<boost/simd/constant/invsqrt_2pi.hpp>}

  @par Description

  1.  @code
      template<typename T> T Invsqrt_2pi();
      @endcode

  2.  @code
      template<typename T> T Invsqrt_2pi( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac{1}{\sqrt{2\pi}}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.39894228040143267793994605993438)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/invsqrt_2pi.hpp>
#include <boost/simd/constant/simd/invsqrt_2pi.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOPI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Twopi Twopi (function template)

  Generates the constant \f$2\pi\f$

  @headerref{<boost/simd/constant/twopi.hpp>}

  @par Description

  1.  @code
      template<typename T> T Twopi();
      @endcode

  2.  @code
      template<typename T> T Twopi( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$2\pi\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(6.283185307179586476925286766559)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/twopi.hpp>
#include <boost/simd/constant/simd/twopi.hpp>

#endif

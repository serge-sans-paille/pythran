//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INV2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INV2PI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Inv2pi Inv2pi (function template)

   Generates the constant \f$\frac{1}{2\pi}\f$.

  @headerref{<boost/simd/constant/inv2pi.hpp>}

  @par Description

  1.  @code
      template<typename T> T Inv2pi();
      @endcode

  2.  @code
      template<typename T> T Inv2pi( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac{1}{2\pi}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.15915494309189533576888376337251)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/inv2pi.hpp>
#include <boost/simd/constant/simd/inv2pi.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVPI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Invpi Invpi (function template)

  Generates the constant \f$\frac1\pi\f$.

  @headerref{<boost/simd/constant/invpi.hpp>}

  @par Description

  1.  @code
      template<typename T> T Invpi();
      @endcode

  2.  @code
      template<typename T> T Invpi( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac1\pi\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.31830988618379067153776752674503)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/invpi.hpp>
#include <boost/simd/constant/simd/invpi.hpp>

#endif

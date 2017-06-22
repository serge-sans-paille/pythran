//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVEPS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Inveps Inveps (function template)

  Generates the constant \f$\frac{1}{\epsilon}\f$

  @headerref{<boost/simd/constant/inveps.hpp>}

  @par Description

  1.  @code
      template<typename T> T Inveps();
      @endcode

  2.  @code
      template<typename T> T Inveps( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to the reciprocal of
  [machine epsilon](https://en.wikipedia.org/wiki/Machine_epsilon).

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `1/Eps<T>()`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/inveps.hpp>
#include <boost/simd/constant/simd/inveps.hpp>

#endif

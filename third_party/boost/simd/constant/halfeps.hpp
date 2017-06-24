//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_HALFEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_HALFEPS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Halfeps Halfeps (function template)

  Generates the constant \f$\frac{1}{2}\epsilon\f$.

  @headerref{<boost/simd/constant/halfeps.hpp>}

  @par Description

  1.  @code
      template<typename T> T Halfeps();
      @endcode

  2.  @code
      template<typename T> T Halfeps( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to half the value of the
  [machine epsilon](https://en.wikipedia.org/wiki/Machine_epsilon).

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `Eps<T>()/2`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/halfeps.hpp>
#include <boost/simd/constant/simd/halfeps.hpp>

#endif

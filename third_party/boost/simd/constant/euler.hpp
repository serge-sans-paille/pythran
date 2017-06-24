//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_EULER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_EULER_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Euler Euler (function template)

  Generates an approximation of the Euler-Mascheroni constant.

  @headerref{<boost/simd/constant/euler.hpp>}

  @par Description

  1.  @code
      template<typename T> T Euler();
      @endcode

  2.  @code
      template<typename T> T Euler( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T evaluating to the Euler-Mascheroni constant defined as:
  \f$\gamma = \lim_{n \rightarrow \infty } \left( 1+ \frac{1}{2} + ... + \frac{1}{n} - \ln(n) \right)\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.57721566490153286060651209008240243104215933593992359)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/euler.hpp>
#include <boost/simd/constant/simd/euler.hpp>

#endif

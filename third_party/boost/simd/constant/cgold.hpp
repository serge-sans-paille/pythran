//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_CGOLD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CGOLD_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Cgold Cgold (function template)

  Generates the Golden Ratio conjugate constant: \f$\frac{1}{\phi}\f$.

  @headerref{<boost/simd/constant/cgold.hpp>}

  @par Description

  1.  @code
      template<typename T> T Cgold();
      @endcode

  2.  @code
      template<typename T> T Cgold( boost::simd::as_<T> const& target );
      @endcode

  Generates a constant that evaluate to the
  [Golden Ratio conjugate](http://mathworld.wolfram.com/GoldenRatioConjugate.html)
  (also known as the silver ratio) defined as \f$\frac{1 - \sqrt{5}}{2}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T((1 - sqrt(5))/2)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/cgold.hpp>
#include <boost/simd/constant/simd/cgold.hpp>

#endif

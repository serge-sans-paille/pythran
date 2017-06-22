//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_GOLD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_GOLD_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Gold Gold (function template)

  Generates the Golden Ratio \f$\phi

  @headerref{<boost/simd/constant/gold.hpp>}

  @par Description

  1.  @code
      template<typename T> T Gold();
      @endcode

  2.  @code
      template<typename T> T Gold( boost::simd::as_<T> const& target );
      @endcode

  Generates a constant that evaluate to the [Golden Ratio](http://mathworld.wolfram.com/GoldenRatio.html)
  defined as \f$\frac{1}{2}(1 + \sqrt{5})\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(1.61803398874989484820458683436563811772)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/gold.hpp>
#include <boost/simd/constant/simd/gold.hpp>

#endif

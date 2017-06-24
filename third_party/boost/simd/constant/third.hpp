//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_THIRD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_THIRD_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Third Third (function template)

  Generates the constant \f$\frac{1}{3}\f$

  @headerref{<boost/simd/constant/third.hpp>}

  @par Description

  1.  @code
      template<typename T> T Third();
      @endcode

  2.  @code
      template<typename T> T Third( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac{1}{3}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `1/T(3)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/third.hpp>
#include <boost/simd/constant/simd/third.hpp>

#endif

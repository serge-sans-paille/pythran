//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_7_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_7_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Fact_7 Fact_7 (function template)

  Generates the @c 7! constant

  @headerref{<boost/simd/constant/fact_7.hpp>}

  @par Description

  1.  @code
      template<typename T> T Fact_7();
      @endcode

  2.  @code
      template<typename T> T Fact_7( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 7!.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to @c T(5040).

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/fact_7.hpp>
#include <boost/simd/constant/simd/fact_7.hpp>

#endif

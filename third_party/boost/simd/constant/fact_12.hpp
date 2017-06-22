//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_12_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_12_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Fact_12 Fact_12 (function template)

  Generates the @c 12! constant

  @headerref{<boost/simd/constant/fact_12.hpp>}

  @par Description

  1.  @code
      template<typename T> T Fact_12();
      @endcode

  2.  @code
      template<typename T> T Fact_12( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 12!.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to @c T(479001600).

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/fact_12.hpp>
#include <boost/simd/constant/simd/fact_12.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_6_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_6_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Fact_6 Fact_6 (function template)

  Generates the @c 6! constant

  @headerref{<boost/simd/constant/fact_6.hpp>}

  @par Description

  1.  @code
      template<typename T> T Fact_6();
      @endcode

  2.  @code
      template<typename T> T Fact_6( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 6!.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to @c T(720).

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/fact_6.hpp>
#include <boost/simd/constant/simd/fact_6.hpp>

#endif

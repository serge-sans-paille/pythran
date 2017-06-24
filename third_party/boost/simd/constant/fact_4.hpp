//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_4_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_4_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Fact_4 Fact_4 (function template)

  Generates the @c 4! constant

  @headerref{<boost/simd/constant/fact_4.hpp>}

  @par Description

  1.  @code
      template<typename T> T Fact_4();
      @endcode

  2.  @code
      template<typename T> T Fact_4( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 4!.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(24)`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/fact_4.hpp>
#include <boost/simd/constant/simd/fact_4.hpp>

#endif

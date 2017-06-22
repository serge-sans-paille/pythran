//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_9_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_9_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Fact_9 Fact_9 (function template)

  Generates the @c 9! constant

  @headerref{<boost/simd/constant/fact_9.hpp>}

  @par Description

  1.  @code
      template<typename T> T Fact_9();
      @endcode

  2.  @code
      template<typename T> T Fact_9( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 9!.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to @c T(362880).

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/fact_9.hpp>
#include <boost/simd/constant/simd/fact_9.hpp>

#endif

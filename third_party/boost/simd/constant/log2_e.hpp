//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOG2_E_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOG2_E_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Log2_e Log2_e (function template)

  Generates the constant \f$\log_2(e)\f$

  @headerref{<boost/simd/constant/log2_e.hpp>}

  @par Description

  1.  @code
      template<typename T> T Log2_e();
      @endcode

  2.  @code
      template<typename T> T Log2_e( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\log_2(e)\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(1.4426950408889634073599246810019)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/log2_e.hpp>
#include <boost/simd/constant/simd/log2_e.hpp>

#endif

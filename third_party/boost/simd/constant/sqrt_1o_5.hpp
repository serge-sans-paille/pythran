//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRT_1O_5_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRT_1O_5_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Sqrt_1o_5 Sqrt_1o_5 (function template)

  Generates the constant \f$ \sqrt{\frac15}\f$

  @headerref{<boost/simd/constant/sqrt_1o_5.hpp>}

  @par Description

  1.  @code
      template<typename T> T Sqrt_1o_5();
      @endcode

  2.  @code
      template<typename T> T Sqrt_1o_5( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$ \sqrt{\frac15}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.44721359549995793928183473374626)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/sqrt_1o_5.hpp>
#include <boost/simd/constant/simd/sqrt_1o_5.hpp>

#endif

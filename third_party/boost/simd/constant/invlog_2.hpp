//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVLOG_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVLOG_2_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Invlog_2 Invlog_2 (function template)

  Generates the constant \f$\frac{1}{\log(2)}\f$

  @headerref{<boost/simd/constant/invlog_2.hpp>}

  @par Description

  1.  @code
      template<typename T> T Invlog_2();
      @endcode

  2.  @code
      template<typename T> T Invlog_2( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac{1}{\log(2)}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(1.442695040888963407359924681001892137426645954152986)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/invlog_2.hpp>
#include <boost/simd/constant/simd/invlog_2.hpp>

#endif

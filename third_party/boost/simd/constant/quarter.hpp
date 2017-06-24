//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_QUARTER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_QUARTER_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Quarter Quarter (function template)

  Generates the constant \f$\frac{1}{4}\f$.

  @headerref{<boost/simd/constant/quarter.hpp>}

  @par Description

  1.  @code
      template<typename T> T Quarter();
      @endcode

  2.  @code
      template<typename T> T Quarter( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 0.25.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T  that evaluates to `T(0.25)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/quarter.hpp>
#include <boost/simd/constant/simd/quarter.hpp>

#endif

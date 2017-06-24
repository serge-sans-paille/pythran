//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWENTY_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWENTY_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Twenty Twenty (function template)

  Generates the constant @c 20

  @headerref{<boost/simd/constant/twenty.hpp>}

  @par Description

  1.  @code
      template<typename T> T Twenty();
      @endcode

  2.  @code
      template<typename T> T Twenty( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 20.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(20)`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/twenty.hpp>
#include <boost/simd/constant/simd/twenty.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SIX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SIX_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Six Six (function template)

  Generates the constant @c 6

  @headerref{<boost/simd/constant/six.hpp>}

  @par Description

  1.  @code
      template<typename T> T Six();
      @endcode

  2.  @code
      template<typename T> T Six( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to 6.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(6)`

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/six.hpp>
#include <boost/simd/constant/simd/six.hpp>

#endif

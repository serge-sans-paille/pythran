//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FALSE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FALSE_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-False False (function template)

  Generates a constant that evaluates to the boolean @c false

  @headerref{<boost/simd/constant/false.hpp>}

  @par Description

  1.  @code
      template<typename T> as_logical_t<T> False();
      @endcode

  2.  @code
      template<typename T> as_logical_t<T> False( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to the boolean @c false

  @par Parameters

  | Name                | Description                                                    |
  |--------------------:|:---------------------------------------------------------------|
  | **target**          | a [placeholder](@ref as) value encapsulating the constant type |

  @par Return Value
  A value of type @c as_logical_t<T> that evaluates to @c as_logical_t<T>(false).

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/false.hpp>
#include <boost/simd/constant/simd/false.hpp>

#endif

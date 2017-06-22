//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MINDENORMAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MINDENORMAL_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Mindenormal Mindenormal (function template)

  Generates the smallest denormal value.

  @headerref{<boost/simd/constant/mindenormal.hpp>}

  @par Description

  1.  @code
      template<typename T> T Mindenormal();
      @endcode

  2.  @code
      template<typename T> T Mindenormal( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluate to the smallest of all non zero positive
  value including denormals.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to

  | Type           | double                        | float                      | Integral |
  |:---------------|:------------------------------|----------------------------|----------|
  | **Values**     |   4.940656458412465e-324      |      1.4012985e-45         |    1     |

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/mindenormal.hpp>
#include <boost/simd/constant/simd/mindenormal.hpp>

#endif

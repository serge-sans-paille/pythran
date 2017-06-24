//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_EPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_EPS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Eps Eps (function template)

  Generates a constant equals to the [machine epsilon](https://en.wikipedia.org/wiki/Machine_epsilon).

  @headerref{<boost/simd/constant/eps.hpp>}

  @par Description

  1.  @code
      template<typename T> T Eps();
      @endcode

  2.  @code
      template<typename T> T Eps( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T equals to the difference between 1 and the next representable
  value of type @c T.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to:

  | Type       | `double`       | `float`       | Integer |
  |:-----------|:---------------|---------------|---------|
  | **Values** | \f$2^{-52}\f$  | \f$2^{-23}\f$ |    1    |

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/eps.hpp>
#include <boost/simd/constant/simd/eps.hpp>

#endif

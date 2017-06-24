//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_THREEEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_THREEEPS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Threeeps Threeeps (function template)

  Generates the constant \f$3\epsilon\f$.

  @headerref{<boost/simd/constant/threeeps.hpp>}

  @par Description

  1.  @code
      template<typename T> T Threeeps();
      @endcode

  2.  @code
      template<typename T> T Threeeps( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to thrice the machine epsilon.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to:

  | Type          | double                        | float         | Integral        |
  |:--------------|:------------------------------|---------------|-----------------|
  | **Values**    |    6.661338147750939e-16      | 3.5762787e-07 | 3               |

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/threeeps.hpp>
#include <boost/simd/constant/simd/threeeps.hpp>

#endif

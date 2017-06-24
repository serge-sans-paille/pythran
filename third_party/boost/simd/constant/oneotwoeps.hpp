//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_ONEOTWOEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_ONEOTWOEPS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Oneotwoeps Oneotwoeps (function template)

  Generates the constant \f$1/(2\epsilon)\f$

  @headerref{<boost/simd/constant/oneotwoeps.hpp>}

  @par Description

  1.  @code
      template<typename T> T Oneotwoeps();
      @endcode

  2.  @code
      template<typename T> T Oneotwoeps( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T evaluating to \f$1/(2\epsilon)\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to

  | Type        | double                      | float                 | Integral  |
  |:------------|:----------------------------|-----------------------|-----------|
  | **Values**  |  \f$2^{52}\f$               | \f$2^{23} \f$         |  0        |

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/oneotwoeps.hpp>
#include <boost/simd/constant/simd/oneotwoeps.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_THIRDROOTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_THIRDROOTEPS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Thirdrooteps Thirdrooteps (function template)

  Generates the constant \f$\sqrt[3]{\epsilon}\f$

  @headerref{<boost/simd/constant/thirdrooteps.hpp>}

  @par Description

  1.  @code
      template<typename T> T Thirdrooteps();
      @endcode

  2.  @code
      template<typename T> T Thirdrooteps( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\sqrt[3]{\epsilon}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to:

  | Type       | double                     | float             |    Integral     |
  |:-----------|:---------------------------|-------------------|-----------------|
  | **Values** |   6.055454452393343e-06    |  4.9215667e-03f   |   1             |

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/thirdrooteps.hpp>
#include <boost/simd/constant/simd/thirdrooteps.hpp>

#endif

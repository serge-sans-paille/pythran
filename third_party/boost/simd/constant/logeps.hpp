//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOGEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOGEPS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Logeps Logeps (function template)

  Generates the constant \f$\log(\epsilon)\f$

  @headerref{<boost/simd/constant/logeps.hpp>}

  @par Description

  1.  @code
      template<typename T> T Logeps();
      @endcode

  2.  @code
      template<typename T> T Logeps( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\log(\epsilon)\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `log(Eps<T>())`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/logeps.hpp>
#include <boost/simd/constant/simd/logeps.hpp>

#endif

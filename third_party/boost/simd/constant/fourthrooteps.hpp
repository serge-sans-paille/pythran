//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FOURTHROOTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FOURTHROOTEPS_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Fourthrooteps Fourthrooteps (function template)

  Generates the constant \f$\sqrt[4]\epsilon\f$.

  @headerref{<boost/simd/constant/fourthrooteps.hpp>}

  @par Description

  1.  @code
      template<typename T> T Fourthrooteps();
      @endcode

  2.  @code
      template<typename T> T Fourthrooteps( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to the fourth root of the machine epsilon.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `sqrt(sqrt(Eps<T>()))`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/fourthrooteps.hpp>
#include <boost/simd/constant/simd/fourthrooteps.hpp>

#endif

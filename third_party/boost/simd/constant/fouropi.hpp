//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FOUROPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FOUROPI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Fouropi Fouropi (function template)

  Generates the constant \f$\frac4\pi\f$.

  @headerref{<boost/simd/constant/fouropi.hpp>}

  @par Description

  1.  @code
      template<typename T> T Fouropi();
      @endcode

  2.  @code
      template<typename T> T Fouropi( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac4\pi\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(1.2732395447351626861510701069801)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/fouropi.hpp>
#include <boost/simd/constant/simd/fouropi.hpp>

#endif

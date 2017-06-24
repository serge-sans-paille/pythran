//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SPLITFACTOR_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SPLITFACTOR_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Splitfactor Splitfactor (function template)

  Generates a constant able to split IEEE values for precision issues

  @headerref{<boost/simd/constant/splitfactor.hpp>}

  @par Description

  1.  @code
      template<typename T> T Splitfactor();
      @endcode

  2.  @code
      template<typename T> T Splitfactor( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to the factor usable to split a IEEE754 value
  into two parts in order to provide precision guarantee for some functions (like
  [two_add](@ref real-two_add) or [two_prod](@ref real-two_prod).

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c as_integer_t<T> that evaluates to

  | Type              | double                        | float         |
  |:------------------|:------------------------------|---------------|
  | **Values**        |   \f$2^{27}\f$                | \f$2^{13}\f$  |

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/splitfactor.hpp>
#include <boost/simd/constant/simd/splitfactor.hpp>

#endif

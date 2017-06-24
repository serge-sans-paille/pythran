//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOG_2OLOG_10_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOG_2OLOG_10_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Log_2olog_10 Log_2olog_10 (function template)

  Generates the constant \f$\frac{\log(2)}{\log(10)}\f$

  @headerref{<boost/simd/constant/log_2olog_10.hpp>}

  @par Description

  1.  @code
      template<typename T> T Log_2olog_10();
      @endcode

  2.  @code
      template<typename T> T Log_2olog_10( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac{\log(2)}{\log(10)}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.3010299956639811952137388947244930267681898814621085)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/log_2olog_10.hpp>
#include <boost/simd/constant/simd/log_2olog_10.hpp>

#endif

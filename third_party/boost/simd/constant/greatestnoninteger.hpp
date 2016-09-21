//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_GREATESTNONINTEGER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_GREATESTNONINTEGER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the least integer value which is exactly
    representable in the type and
    equal to its integral successor.

    All floating numbers greater than Greatestnoninteger are integral.

    @par Semantic:

    @code
    T r = Greatestnoninteger<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 0
    else if T is double
      r = 4503599627370495.5
    else if T is float
      r = 8388607.5f
    @endcode

    @return The Greatestnoninteger constant for the proper type
  **/
  template<typename T> T Greatestnoninteger();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant greatestnoninteger.

      @return The Greatestnoninteger constant for the proper type
    **/
    Value Greatestnoninteger();
  }
} }
#endif

#include <boost/simd/constant/definition/greatestnoninteger.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

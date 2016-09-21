//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_QUARTER_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_QUARTER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate t value 1/4

    @par Semantic:

    @code
    T r = Quarter<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(4);
    @endcode

    @return The Quarter constant for the proper type
  **/
  template<typename T> T Quarter();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant quarter.

      @return The Quarter constant for the proper type
    **/
    Value Quarter();
  }
} }
#endif

#include <boost/simd/constant/definition/quarter.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

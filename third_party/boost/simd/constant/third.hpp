//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_THIRD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_THIRD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate value 1/3

    @par Semantic:

    @code
    T r = Third<T>();
    @endcode

    is similar to:

    @code
    T r = T(1)/T(3);
    @endcode

    @return The Third constant for the proper type
  **/
  template<typename T> T Third();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant third.

      @return The Third constant for the proper type
    **/
    Value Third();
  }
} }
#endif

#include <boost/simd/constant/definition/third.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

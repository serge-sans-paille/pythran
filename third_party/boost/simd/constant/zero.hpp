//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_ZERO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_ZERO_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate  value 0

    @par Semantic:

    @code
    T r = Zero<T>();
    @endcode

    is similar to:

    @code
    T r = T(0);
    @endcode

    @return The Zero constant for the proper type
  **/
  template<typename T> T Zero();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant zero.

      @return The Zero constant for the proper type
    **/
    Value Zero();
  }
} }
#endif

#include <boost/simd/constant/definition/zero.hpp>
#include <boost/simd/arch/common/scalar/constant/zero.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/zero.hpp>
#endif

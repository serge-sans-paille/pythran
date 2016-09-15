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

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the  logarithm of the Eps constant.

    @par Semantic:

    @code
    T r = Logeps<T>();
    @endcode

    is similar to:

    @code
      r =  log(Eps<T>());
    @endcode

    @return The Logeps constant for the proper type
  **/
  template<typename T> T Logeps();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant logeps.

      @return The Logeps constant for the proper type
    **/
    Value Logeps();
  }
} }
#endif

#include <boost/simd/constant/definition/logeps.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

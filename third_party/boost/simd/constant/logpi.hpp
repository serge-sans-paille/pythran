//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOGPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOGPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate value \f$\log\pi\f$

    @par Semantic:

    @code
    T r = Logpi<T>();
    @endcode

    is similar to:

    @code
    T r = log(Pi<T>());
    @endcode

    @return The Logpi constant for the proper type
  **/
  template<typename T> T Logpi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant logpi.

      @return The Logpi constant for the proper type
    **/
    Value Logpi();
  }
} }
#endif

#include <boost/simd/constant/definition/logpi.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOGSQRT2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOGSQRT2PI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate value \f$\log\sqrt{2\pi}\f$

    @par Semantic:

    @code
    T r = Logsqrt2pi<T>();
    @endcode

    is similar to:

    @code
    T r = log(sqrt(2*Pi<T>());
    @endcode

    @return The Logsqrt2pi constant for the proper type
  **/
  template<typename T> T Logsqrt2pi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant logsqrt2pi.

      @return The Logsqrt2pi constant for the proper type
    **/
    Value Logsqrt2pi<Value>();
  }
} }
#endif

#include <boost/simd/constant/definition/logsqrt2pi.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

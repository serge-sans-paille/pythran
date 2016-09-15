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

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant Log_2olog_10 : \f$\frac{\log(2)}{\log(10)}\f$.

    @par Semantic:

    @code
    T r = Log_2olog_10<T>();
    @endcode

    is similar to:

    @code
      r =  T(0.3010299956639811952137388947244930267681898814621085);
    @endcode


**/
  template<typename T> T Log_2olog_10();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant Log_2olog_10.  (\f$\frac{\log(2)}{\log(10)}\f$)

      Generate the  constant log_2olog_10.

      @return The Log_2olog_10 constant for the proper type
    **/
    Value Log_2olog_10<Value>();
  }
} }
#endif

#include <boost/simd/constant/definition/log_2olog_10.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

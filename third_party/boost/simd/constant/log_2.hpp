//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOG_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOG_2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant Log_2 : \f$\log(2)\f$.

    @par Semantic:

    @code
    T r = Log_2<T>();
    @endcode

    is similar to:

    @code
      r =  T(0.6931471805599453094172321214581765680755001343602553);
    @endcode


**/
  template<typename T> T Log_2();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant Log_2. (\f$\log(2)\f$)

      Generate the  constant log_2.

      @return The Log_2 constant for the proper type
    **/
    const boost::dispatch::functor<tag::log_2_> log_2 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/log_2.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

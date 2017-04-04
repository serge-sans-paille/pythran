//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_POW_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_POW_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object computes \f$x^y\f$

    @par Header <boost/simd/function/pow.hpp>

    @par Decorators
      - std_ decorator calls @c std:pow

      - raw_ decorator almost nearly uses the naive formula (\f$e^{y\log x}\f$)
         and so does not care for limits and leads to lower accuracy


    @par Example:

      @snippet pow.cpp pow

    @par Possible output:

      @snippet pow.txt pow

  **/
  ///@{
  IEEEValue pow(IEEEValue const& x, Value const& y);
  IntegerValue pow(IntegerValue const& x, IntegerValue const& y);
  ///@}
} }
#endif

#include <boost/simd/function/scalar/pow.hpp>
#include <boost/simd/function/simd/pow.hpp>

#endif

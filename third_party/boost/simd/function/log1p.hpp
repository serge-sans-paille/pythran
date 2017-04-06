//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOG1P_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOG1P_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object computes \f$\log(1+x)\f$ with good accuracy even for small
    \f$x\f$ values.

    @par Header <boost/simd/function/log1p.hpp>

    @par Decorators

      - std_ for floating entries calls @c std::log1p

    @see log, exp, expm1

    @par Example:

      @snippet log1p.cpp log1p

    @par Possible output:

      @snippet log1p.txt log1p

  **/
  IEEEValue log1p(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/log1p.hpp>
#include <boost/simd/function/simd/log1p.hpp>

#endif

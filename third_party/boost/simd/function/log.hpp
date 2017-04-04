//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object returns the natural logarithm of its argument.

    @par Header <boost/simd/function/log.hpp>

    @see log10, log2, log1p

    @par Note:

    - log(x) return Nan for negative entries (peculiarly Mzero
    for floating numbers).

    @par Decorators

      - std_ for floating entries calls @c std::log


    @par Example:

      @snippet log.cpp log

    @par Possible output:

      @snippet log.txt log

  **/
  IEEEValue log(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/log.hpp>
#include <boost/simd/function/simd/log.hpp>

#endif

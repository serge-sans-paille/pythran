//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOG2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOG2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object returns the base two logarithm of its argument.

    @par Header <boost/simd/function/log2.hpp>

    @par Decorators

      - std_ for floating entries calls @c std::log2

    @see log10, log, log1p

    @par Example:

      @snippet log2.cpp log2

    @par Possible output:

      @snippet log2.txt log2

  **/
  IEEEValue log2(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/log2.hpp>
#include <boost/simd/function/simd/log2.hpp>

#endif

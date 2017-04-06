//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXP10_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXP10_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object returns the base ten exponential of its argument: \f$10^{x}\f$

    @par Header <boost/simd/function/exp10.hpp>

    @par Note:

    provisions are made for obtaining a flint result from a flint argument.

    @see exp2, exp, pow


    @par Example:

      @snippet exp10.cpp exp10

    @par Possible output:

      @snippet exp10.txt exp10

  **/
  IEEEValue exp10(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/exp10.hpp>
#include <boost/simd/function/simd/exp10.hpp>

#endif

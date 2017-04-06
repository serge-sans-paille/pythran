//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object returns the exponential of its argument: \f$e^{x}\f$

    @par Header <boost/simd/function/exp.hpp>


    @par Decorators

      - std_ for floating entries calls @c std::exp

    @see exp2, exp10, pow, expm1, log


    @par Example:

      @snippet exp.cpp exp

    @par Possible output:

      @snippet exp.txt exp

  **/
  IEEEValue exp(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/exp.hpp>
#include <boost/simd/function/simd/exp.hpp>

#endif

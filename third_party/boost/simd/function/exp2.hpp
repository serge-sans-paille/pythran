//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXP2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXP2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object returns the base two exponential of its argument: \f$2^{x}\f$

    @par Header <boost/simd/function/exp2.hpp>

    @par Note:

    - provisions are made to obtain a flint result from a flint argument

    @par Decorators

      - std_ for floating entries calls @c std::exp2

    @see exp, exp10, pow, pow2


    @par Example:

      @snippet exp2.cpp exp2

    @par Possible output:

      @snippet exp2.txt exp2

  **/
  IEEEValue exp2(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/exp2.hpp>
#include <boost/simd/function/simd/exp2.hpp>

#endif

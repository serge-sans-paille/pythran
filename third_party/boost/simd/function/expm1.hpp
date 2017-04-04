//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXPM1_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXPM1_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object returns the exponential of its argument minus one:\f$e^{x}-1\f$

    @par Header <boost/simd/function/expm1.hpp>

    @par Notes

    - result is accurate even for @c x of small modulus

    @par Decorators

     - std_ for floating entries calls @c std::expm1

    @see exp


    @par Example:

      @snippet expm1.cpp expm1

    @par Possible output:

      @snippet expm1.txt expm1

  **/
  IEEEValue expm1(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/expm1.hpp>
#include <boost/simd/function/simd/expm1.hpp>

#endif

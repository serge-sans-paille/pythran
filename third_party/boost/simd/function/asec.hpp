//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ASEC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ASEC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the inverse secant in radian: \f$\arccos(1/x)\f$.

    @par Header <boost/simd/function/asec.hpp>

    @see asecd, asecpi

    @par Example:

      @snippet asec.cpp asec

    @par Possible output:

      @snippet asec.txt asec

  **/
  IEEEValue asec(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/asec.hpp>
#include <boost/simd/function/simd/asec.hpp>

#endif

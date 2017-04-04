//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SECH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SECH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-hyperbolic
    This function object returns the hyperbolic secant: \f$1/\cosh(x)\f$.


    @see cosh, sinh, tanh, csch, sinhcosh


    @par Header <boost/simd/function/sech.hpp>

    @par Example:

      @snippet sech.cpp sech

    @par Possible output:

      @snippet sech.txt sech

  **/
  IEEEValue sech(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/sech.hpp>
#include <boost/simd/function/simd/sech.hpp>

#endif

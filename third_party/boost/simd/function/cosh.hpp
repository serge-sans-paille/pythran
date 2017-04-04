//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COSH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COSH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-hyperbolic
    This function object returns the hyperbolic cosine: \f$(e^{x}+e^{-x})/2\f$.

    @see sinh, tanh, sech, csch, sinhcosh


    @par Header <boost/simd/function/cosh.hpp>

    @par Example:

      @snippet cosh.cpp cosh

    @par Possible output:

      @snippet cosh.txt cosh
  **/
  IEEEValue cosh(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/cosh.hpp>
#include <boost/simd/function/simd/cosh.hpp>

#endif

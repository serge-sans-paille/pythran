//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_TANH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_TANH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-hyperbolic
    This function object returns the hyperbolic tangent: \f$\sinh(x)/\cosh(x)\f$.

    @see sinh, cosh, sech, csch, sinhcosh


    @par Header <boost/simd/function/tanh.hpp>

    @par Example:

      @snippet tanh.cpp tanh

    @par Possible output:

      @snippet tanh.txt tanh
  **/
  IEEEValue tanh(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/tanh.hpp>
#include <boost/simd/function/simd/tanh.hpp>

#endif

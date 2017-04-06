//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ASINH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ASINH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-hyperbolic
    This function object returns the hyperbolic sine argument: \f$\log(x+\sqrt{x^2+1})\f$.

    @par Header <boost/simd/function/asinh.hpp>

    @see log, sqrt, sinh, inc

    @par Example:

      @snippet asinh.cpp asinh

    @par Possible output:

      @snippet asinh.txt asinh

  **/
  IEEEValue asinh(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/asinh.hpp>
#include <boost/simd/function/simd/asinh.hpp>

#endif

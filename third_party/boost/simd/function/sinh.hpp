//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-hyperbolic
    This function object returns the hyperbolic sine: \f$(e^{x}-e^{-x})/2\f$.

    @par Header <boost/simd/function/sinh.hpp>

    @see tanh, cosh, sech, csch, sinhcosh

    @par Example:

      @snippet sinh.cpp sinh

    @par Possible output:

      @snippet sinh.txt sinh
  **/
  IEEEValue sinh(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/sinh.hpp>
#include <boost/simd/function/simd/sinh.hpp>

#endif

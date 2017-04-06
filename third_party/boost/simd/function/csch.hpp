//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CSCH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CSCH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-hyperbolic
    This function object returns the hyperbolic cosecant: \f$1/\sinh(1/x)\f$.

    @par Header <boost/simd/function/csch.hpp>

    @see sinh, tanh, sech, csch, sinhcosh

    @par Example:

      @snippet csch.cpp csch

    @par Possible output:

      @snippet csch.txt csch
  **/
  IEEEValue csch(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/csch.hpp>
#include <boost/simd/function/simd/csch.hpp>

#endif

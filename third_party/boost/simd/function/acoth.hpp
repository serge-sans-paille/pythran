//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOTH_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOTH_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-hyperbolic
    This function object returns the hyperbolic cotangent argument \f$\frac12\log\frac{x+1}{x-1}\f$


    @see cosh, sinh, acosh, asinh, atanh, asech, acosh, acsch


    @par Header <boost/simd/function/acoth.hpp>

    @par Example:

      @snippet acoth.cpp acoth

    @par Possible output:

      @snippet acoth.txt acoth

  **/
  IEEEValue acoth(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/acoth.hpp>
#include <boost/simd/function/simd/acoth.hpp>

#endif

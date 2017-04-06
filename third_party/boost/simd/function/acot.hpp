//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the inverse cotangent.


    @par Header <boost/simd/function/acot.hpp>

    @par Note

      For every parameter of floating type `r = acot(x)`
      returns the arc @c r in the interval  \f$[0, \pi[\f$ such that
      <tt>cot(r) == x</tt>.

    @see acotd, acotpi, cot


    @par Example:

      @snippet acot.cpp acot

    @par Possible output:

      @snippet acot.txt acot

  **/
  IEEEValue acot(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/acot.hpp>
#include <boost/simd/function/simd/acot.hpp>

#endif

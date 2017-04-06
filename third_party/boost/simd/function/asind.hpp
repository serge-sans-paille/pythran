//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ASIND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ASIND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the inverse sine in degree.


    @par Header <boost/simd/function/asind.hpp>

    @par Note

      For every parameter of floating type `asind(x)`
      returns the arc @c r in the interval  \f$[-90, 90[\f$ such that
      <tt>sin(r) == x</tt>.  If @c x is outside \f$[-1, 1[\f$ the result is Nan.

    @see asin,  asinpi

    @par Example:

      @snippet asind.cpp asind

    @par Possible output:

      @snippet asind.txt asind

  **/
  IEEEValue asind(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/asind.hpp>
#include <boost/simd/function/simd/asind.hpp>

#endif

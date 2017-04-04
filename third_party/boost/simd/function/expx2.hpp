//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXPX2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXPX2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object returns the exponential of the square of its
    argument or its inverse: \f$e^{x^2}\f$ or \f$e^{-x^2}\f$.
    The sign chosen is -1 if and only if the sign bit of the second argument is not zero.


    @par Header <boost/simd/function/expx2.hpp>

    @par Note:
    provisions are made for obtaining more accurate results for large @c x.
    The second argument @c s defaults to 1.

    @see exp


    @par Example:

      @snippet expx2.cpp expx2

    @par Possible output:

      @snippet expx2.txt expx2

  **/
   IEEEValue expx2(IEEEValue const& x, IEEEValue const& s = 1);

} }
#endif

#include <boost/simd/function/scalar/expx2.hpp>
#include <boost/simd/function/simd/expx2.hpp>

#endif

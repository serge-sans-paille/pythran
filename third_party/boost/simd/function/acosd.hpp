//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACOSD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACOSD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the inverse cosine in degree.


    @par Header <boost/simd/function/acosd.hpp>

    @par Decorators

       - pedantic_     is similar to indeg(pedantic_)(acos(x));

    @see acos, acospi, cosd, indeg


    @par Example:

      @snippet acosd.cpp acosd

    @par Possible output:

      @snippet acosd.txt acosd

  **/
  IEEEValue acosd(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/acosd.hpp>
#include <boost/simd/function/simd/acosd.hpp>

#endif

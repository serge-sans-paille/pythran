//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COSPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COSPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-trigonometric
    This function object returns the cosine of angle in
    \f$\pi\f$ multiples: \f$\cos(\pi x)\f$.


    @par Header <boost/simd/function/cospi.hpp>

    @par Note

     -  The semantics of the function are similar to @ref cos ones.
        See @ref cos for further details

     - As it conveys a peculiar meaning,  unlike the other cosine, cospi is defined
         for integral types and the result of cospi(n) coincides with \f$(-1)^n\f$.

         Take care that large floating entries are always integral and even !

    @see sincospi, cos, cosd


    @par Example:

      @snippet cospi.cpp cospi

    @par Possible output:

      @snippet cospi.txt cospi

  **/
  Value cospi(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/cospi.hpp>
#include <boost/simd/function/simd/cospi.hpp>

#endif

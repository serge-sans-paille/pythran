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
    Function object implementing cospi capabilities

    cosine of angle in \f$\pi\f$ multiples: \f$\cos(\pi x)\f$.

    @par Semantic:

   The semantics of the function are similar to @ref cos ones.
    see @ref cos for further details

    @par Note

    However as it conveys a peculiar meaning,  unlike the orher cosine, cospi is defined
    for integral types and the result of cospi(n) coincides with \f$(-1)^n\f$.

    Take care that large floating entries are always integral and even !

    @see sincospi, cos, cosd

  **/
  Value cospi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cospi.hpp>
#include <boost/simd/function/simd/cospi.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SECPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SECPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing secpi capabilities

    secant of the angle in pi multiples: \f$1/\cos(\pi x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = secpi(x);
    @endcode

    @see secd, sec, cospi, cos

  **/
  Value secpi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/secpi.hpp>
#include <boost/simd/function/simd/secpi.hpp>

#endif

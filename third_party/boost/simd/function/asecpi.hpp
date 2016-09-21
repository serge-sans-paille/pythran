//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ASECPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ASECPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing asecpi capabilities

     inverse secant in \$f\pi\$f multiples: \f$(1/\pi) \arccos(1/x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = asecpi(x);
    @endcode

    @see asec, asecd, cospi, acospi

  **/
  Value asecpi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/asecpi.hpp>
#include <boost/simd/function/simd/asecpi.hpp>

#endif

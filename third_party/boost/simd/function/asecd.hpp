//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ASECD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ASECD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing asecd capabilities

     inverse secant in degree: \f$(180/\pi) \arccos(1/x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = asecd(x);
    @endcode

    @see asec, ascpi, secd, acosd

  **/
  Value asecd(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/asecd.hpp>
#include <boost/simd/function/simd/asecd.hpp>

#endif

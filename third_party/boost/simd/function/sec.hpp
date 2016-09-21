//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SEC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SEC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing sec capabilities

    secant of the angle in radian: \f$1/\cos(x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = sec(x);
    @endcode

    @see cos, secd, secpi, rec

  **/
  Value sec(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sec.hpp>
#include <boost/simd/function/simd/sec.hpp>

#endif

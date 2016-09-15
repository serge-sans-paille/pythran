//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ASEC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ASEC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing asec capabilities

    inverse secant in radian: \f$\arccos(1/x)\f$.

    @par Semantic:

    For every parameter of floating type T

    @code
    auto r = asec(x);
    @endcode

    @see asecd, asecpi, sec, cos

  **/
  Value asec(Value const & x);
} }
#endif

#include <boost/simd/function/scalar/asec.hpp>
#include <boost/simd/function/simd/asec.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ACSCD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ACSCD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing acscd capabilities

    inverse cosecant in degree: \f$(180/\pi) \arcsin(1/x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = acscd(x);
    @endcode

    @see acsc, acscpi, asind, sind

  **/
  Value acscd(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/acscd.hpp>
#include <boost/simd/function/simd/acscd.hpp>

#endif

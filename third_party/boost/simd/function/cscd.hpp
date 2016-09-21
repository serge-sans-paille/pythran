//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CSCD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CSCD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing cscd capabilities

    cosecant in degree: \f$\sin(180/(\pi x))\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = cscd(x);
    @endcode

    As most other trigonometric function cscd can be called with a second optional parameter
    which is a tag on speed and accuracy (see @ref cos for further details)

    @see csc, cscpi,

  **/
  Value cscd(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cscd.hpp>
#include <boost/simd/function/simd/cscd.hpp>

#endif

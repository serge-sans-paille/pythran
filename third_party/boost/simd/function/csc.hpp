//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CSC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CSC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing csc capabilities

    cosecante of the input in radian : \f$\sin(1/x)\f$.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = csc(x);
    @endcode

    As most other trigonometric function csc can be called with a second optional parameter
    which is a tag on speed and accuracy (see @ref cos for further details)

    @see cscd, cscpi,

  **/
  Value csc(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/csc.hpp>
#include <boost/simd/function/simd/csc.hpp>

#endif

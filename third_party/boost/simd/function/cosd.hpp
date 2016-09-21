//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COSD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COSD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing cosd capabilities

    cosine of the input in degree: \f$\cos(\pi x/180)\f$.

    @par Semantic:

    The semantics of the function are similar to @ref cos ones.
    see @ref cos for further details

    @see sincosd, cos, cospi

  **/
  Value cosd(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cosd.hpp>
#include <boost/simd/function/simd/cosd.hpp>

#endif

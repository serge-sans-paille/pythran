//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_INDEG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_INDEG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing indeg capabilities

    convert radian to degree.

    @par Semantic:

    For every parameter of floating type

    @code
    auto r = indeg(x);
    @endcode

    is similar to:

    @code
    auto r = Radindeg*x;
    @endcode

    @see  inrad, Radindeg, Radindegr, Deginrad

  **/
  Value indeg(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/indeg.hpp>
#include <boost/simd/function/simd/indeg.hpp>

#endif

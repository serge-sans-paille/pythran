//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FRAC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FRAC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing frac capabilities

    This function returns the fractional part of the input

    @par Semantic:

    @code
    auto r = frac(x);
    @endcode

    is similar to:

    @code
    auto r =  x-trunc(x);
    @endcode

    @see trunc, modf

  **/
  Value frac(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/frac.hpp>
#include <boost/simd/function/simd/frac.hpp>

#endif

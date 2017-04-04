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
    This function object returns the fractional part of the input i.e. `x-trunc(x)`.

    @see trunc, modf


    @par Header <boost/simd/function/frac.hpp>

    @par Example:

      @snippet frac.cpp frac

    @par Possible output:

      @snippet frac.txt frac

  **/
  Value frac(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/frac.hpp>
#include <boost/simd/function/simd/frac.hpp>

#endif

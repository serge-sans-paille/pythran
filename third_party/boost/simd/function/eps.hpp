//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EPS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EPS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-ieee
    This object function computes the distance between its argument and the next
    representable value of its argument type.


    @see ulp, ulpdist, Eps


    @par Header <boost/simd/function/eps.hpp>

    @par Example:

      @snippet eps.cpp eps

    @par Possible output:

      @snippet eps.txt eps

  **/
  Value eps(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/eps.hpp>
#include <boost/simd/function/simd/eps.hpp>

#endif

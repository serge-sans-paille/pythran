//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ICEIL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ICEIL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the integer conversion of the @ref ceil of its parameter.


    @par Header <boost/simd/function/iceil.hpp>

    @par Note:
    This operation is properly saturated

    @see ceil, ifloor, iround, ifix, inearbyint

    @par Example:

      @snippet iceil.cpp iceil

    @par Possible output:

      @snippet iceil.txt iceil


  **/
  as_integer_t<Value> iceil(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/iceil.hpp>
#include <boost/simd/function/simd/iceil.hpp>

#endif

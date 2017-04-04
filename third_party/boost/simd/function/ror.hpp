//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ROR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ROR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the first entry rotated right
    by the value of the second entry.


    @par Header <boost/simd/function/ror.hpp>

    @par Note
    This function asserts if the integral parameter is out of range

    @see  rol, rror, rrol


    @par Example:

      @snippet ror.cpp ror

    @par Possible output:

      @snippet ror.txt ror

  **/
  Value ror(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/ror.hpp>
#include <boost/simd/function/simd/ror.hpp>

#endif

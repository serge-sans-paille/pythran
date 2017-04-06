//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ROL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ROL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the first entry rotated left
    by the value of the second entry.


    @par Header <boost/simd/function/rol.hpp>

    @par Note
    This function asserts if the integral parameter is out of range

    @see  ror, rrol, rror


    @par Example:

      @snippet rol.cpp rol

    @par Possible output:

      @snippet rol.txt rol

  **/
  Value rol(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/rol.hpp>
#include <boost/simd/function/simd/rol.hpp>

#endif

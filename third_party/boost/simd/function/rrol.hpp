//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_RROL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_RROL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the first entry rotated left or right
    by the absolute value of the second entry,
    according to its sign.


    @par Header <boost/simd/function/rrol.hpp>

    @par Note
    This function asserts if the integral parameter is out of range

    @see  ror, rol, rror


    @par Example:

      @snippet rrol.cpp rrol

    @par Possible output:

      @snippet rrol.txt rrol

  **/
  Value rrol(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/rrol.hpp>
#include <boost/simd/function/simd/rrol.hpp>

#endif

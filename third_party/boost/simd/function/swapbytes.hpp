//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SWAPBYTES_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-bitwise
    This function object reverses the byte order of each scalar element of the parameter.

    @par Header <boost/simd/function/swapbytes.hpp>

    @see reverse,  reversebits

    @par Example:

      @snippet swapbytes.cpp swapbytes

    @par Possible output:

      @snippet swapbytes.txt swapbytes

  **/
  Value swapbytes(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/swapbytes.hpp>
#include <boost/simd/function/simd/swapbytes.hpp>

#endif

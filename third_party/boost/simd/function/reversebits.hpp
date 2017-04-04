//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REVERSEBITS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REVERSEBITS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the bits in reverse order for each scalar entry.

    @see reverse,  swapbytes


    @par Header <boost/simd/function/reversebits.hpp>

    @par Example:

      @snippet reversebits.cpp reversebits

    @par Possible output:

      @snippet reversebits.txt reversebits

  **/
  IntegerValue reversebits(IntegerValue const& x);
} }
#endif

#include <boost/simd/function/scalar/reversebits.hpp>
#include <boost/simd/function/simd/reversebits.hpp>

#endif

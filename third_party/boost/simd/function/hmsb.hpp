//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_HMSB_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_HMSB_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction

    Returns a bs::bitset build from the most significant bit of each value its
    argument.

    @par Header <boost/simd/function/hmsb.hpp>

    @par Example:

      @snippet hmsb.cpp hmsb

    @par Possible output:

      @snippet hmsb.txt hmsb

    @param  v Value to process
    @return A bitset-like structure of the size of cardinal(v) containing the most significant
            bits of each elements of v.
  **/
  bitset<cardinal_of<Value>::value> hmsb(Value const &v);
} }
#endif

#include <boost/simd/function/scalar/hmsb.hpp>
#include <boost/simd/function/simd/hmsb.hpp>

#endif

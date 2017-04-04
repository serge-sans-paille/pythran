//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FIRSTBITUNSET_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FIRSTBITUNSET_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the bit pattern in which the only bit set is
    the first bit unset (beginning with the least significant bit) in the parameter.

    @see  ffs,  firstbitset



    @par Header <boost/simd/function/firstbitunset.hpp>

    @par Example:

      @snippet firstbitunset.cpp firstbitunset

    @par Possible output:

      @snippet firstbitunset.txt firstbitunset

  **/
  as_integer_t<Value> firstbitunset(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/firstbitunset.hpp>
#include <boost/simd/function/simd/firstbitunset.hpp>

#endif

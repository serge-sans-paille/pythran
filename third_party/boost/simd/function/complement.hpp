//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_COMPLEMENT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-operator
    This function object returns the return the bitwise complement of the entry
    Infix notation can be used with operator '~'


    @par Header <boost/simd/function/complement.hpp>

    @par Example:

      @snippet complement.cpp complement

    @par Possible output:

      @snippet complement.txt complement

    @par Alias
    bitwise_not

    @see  bitwise_and, bitwise_or, bitwise_xor, bitwise_notand,
    bitwise_andnot, bitwise_notor, bitwise_ornot

  **/
  Value complement(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/complement.hpp>
#include <boost/simd/function/simd/complement.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITINTEGER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITINTEGER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing bitinteger capabilities

    Transforms a floating point value in a pattern of bits
    stored in an integer with different formulas according to
    the floating point @ref bitofsign.

    This function is the converse of @ref bitfloating.

    @par Semantic:

    for any parameter @c x of floating type @c T

    @code
     as_integer_t<T> r = bitinteger(x);
    @endcode

    @par Note:
    This is an internally used utility function related to the computation of floating
    successors or predecessors

    @see next, prev, successor,  predecessor,  nextafter, bitfloating

  **/
  as_integer_t<T> bitinteger(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/bitinteger.hpp>
#include <boost/simd/function/simd/bitinteger.hpp>

#endif

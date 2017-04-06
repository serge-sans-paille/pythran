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
    This function object transforms a floating point value
    in an integer with a preserving order formula.
    This function is the converse of @ref bitfloating.



    @par Header <boost/simd/function/bitinteger.hpp>

    @par Note:
    This function is related to the computation of
    floating successors or predecessors as the ordering of the integers obtained
    by @c bifloating is the same as the original order on the floating elements,
    an increment can be used to find the successor.

    @see next, prev, successor,  predecessor,  nextafter, bitfloating


    @par Example:

      @snippet bitinteger.cpp bitinteger

    @par Possible output:

      @snippet bitinteger.txt bitinteger

  **/
  as_integer_t<Value> bitinteger(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/bitinteger.hpp>
#include <boost/simd/function/simd/bitinteger.hpp>

#endif

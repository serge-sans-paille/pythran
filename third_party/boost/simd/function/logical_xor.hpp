//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOGICAL_XOR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOGICAL_XOR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object returns the logical xor of the first argument
    and of the second argument.

    @par Header <boost/simd/function/logical_xor.hpp>

    @par Note

    - The result type is the logical type associated to the first argument.

    @pre The operands must share the same @ref cardinal_of value.


    @see logical_not,  logical_and, logical_andnot,  logical_notand,  logical_or, logical_ornot,  logical_notor

    @par Example:

      @snippet logical_xor.cpp logical_xor

    @par Possible output:

      @snippet logical_xor.txt logical_xor

  **/
  as_logical_t<Value0> logical_xor(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/logical_xor.hpp>
#include <boost/simd/function/simd/logical_xor.hpp>

#endif

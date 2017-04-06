//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOGICAL_AND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOGICAL_AND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object returns the logical and of its two parameters.

    Infix notation can be used with operator '&&'.

    @par Note

    - The result type is the logical type associated to the first argument.

    @pre The operands must share the same @ref cardinal_of value.

    @warningbox{Take care that SIMD logical operation do not short-circuit.}

    @par Header <boost/simd/function/logical_and.hpp>

    @see logical_not,  logical_xor, logical_andnot,  logical_notand,  logical_or, logical_ornot,  logical_notor

    @par Example:

      @snippet logical_and.cpp logical_and

    @par Possible output:

      @snippet logical_and.txt logical_and

  **/
  as_logical_t<Value0> logical_and(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/logical_and.hpp>
#include <boost/simd/function/simd/logical_and.hpp>

#endif

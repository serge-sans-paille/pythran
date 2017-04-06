//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOGICAL_NOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object returns the return the logical negation of the argument.

    Infix notation can be used with operator '!'

    @par Header <boost/simd/function/logical_not.hpp>

    @see logical_notor,  logical_xor, logical_andnot,  logical_notand,  logical_ornot, logical_and,  logical_or

    @par Example:

      @snippet logical_not.cpp logical_not

    @par Possible output:

      @snippet logical_not.txt logical_not

  **/
  as_logical_t<Value0> logical_not(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/logical_not.hpp>
#include <boost/simd/function/simd/logical_not.hpp>

#endif

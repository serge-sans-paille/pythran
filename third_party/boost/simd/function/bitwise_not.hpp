//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITWISE_NOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITWISE_NOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-operator
    Function object implementing bitwise_not capabilities

    return the bitwise bitwise_not of the entry
    Infix notation can be used with operator '~'

    This is a convenience alias of @ref complement
  **/
  Value bitwise_not(Value const & x);
} }
#endif

#include <boost/simd/function/scalar/complement.hpp>
#include <boost/simd/function/simd/bitwise_not.hpp>

#endif

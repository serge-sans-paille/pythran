//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!
    @ingroup group-boolean
    Function object implementing if_else capabilities

    If cond is @ref True returns t else returns f

    If vectors, the types involved in the call must share the same number of elements.

    @par Semantic:

    For every parameters @c c of type @c C, @c t and @c f of type @c T:

    @code
    T r = if_else(cond,t,f);
    @endcode

    is similar to:

    @code
    T r = cond ? t : f;
    @endcode

    @see  if_else_zero, if_else_allbits, if_zero_else,
    if_allbits_else, if_one_else_zero, if_zero_else_one, bitwise_select
  **/
  Value if_else(Value const& c, Value const& v0);

  //@overload
  Value if_else(LogicalValue const& c, Value const& v0);
} }
#endif

#include <boost/simd/function/scalar/if_else.hpp>
#include <boost/simd/function/simd/if_else.hpp>

#endif

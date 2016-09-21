//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ZERO_ELSE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ZERO_ELSE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing if_zero_else capabilities

    If cond is @ref True returns @ref Zero else returns f

    @par Semantic:

    For every parameters @c c of type @c C and @c x of type @c T:

    @code
    T r = if_zero_else(cond, x);
    @endcode

    is similar to:

    @code
    T r = cond ? Zero<T>() : x;
    @endcode

  **/
  Value if_zero_else(Value const& c, Value const& x);

  //@overload
  Value if_zero_else(LogicalValue const& c, Value const& x);
} }
#endif

#include <boost/simd/function/scalar/if_zero_else.hpp>
#include <boost/simd/function/simd/if_zero_else.hpp>

#endif

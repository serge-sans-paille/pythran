//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ELSE_ZERO_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing if_else_zero capabilities

    If x is @ref True returns t else returns zero

    @par Semantic:

    For every parameters @c c of type @c C and @c t of type @c T:

    @code
    T r = if_else_zero(cond,t);
    @endcode

    is similar to:

    @code
    T r = cond ? t : Zero<T>();
    @endcode

  **/
  Value if_else_zero(Value const& cond, Value const& t);

  //@overload
  Value if_else_zero(LogicalValue const& cond, Value const& t);
} }
#endif

#include <boost/simd/function/scalar/if_else_zero.hpp>
#include <boost/simd/function/simd/if_else_zero.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_DEC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_DEC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing if_dec capabilities

    Decrements a value by @ref One if a predicate is @ref True.

    @par Semantic:

    For every parameters @c c of type @c C and @c t of type @c T:

    @code
    T r = if_dec(cond,t);
    @endcode

    is similar to:

    @code
    T r = cond ? t-One<T>() : t;
    @endcode
  **/
  Value if_dec(Value const& c, Value const& v0);

  //@overload
  Value if_dec(LogicalValue const& c, Value const& v0);
} }
#endif

#include <boost/simd/function/scalar/if_dec.hpp>
#include <boost/simd/function/simd/if_dec.hpp>

#endif

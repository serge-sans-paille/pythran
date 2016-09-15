//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ALLBITS_ELSE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ALLBITS_ELSE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing if_allbits_else capabilities

    If cond is @ref True returns allbits else returns f

    @par Semantic:

    For every parameters @c cond of type @c C, @c f of type @c T:

    @code
    T r = if_allbits_else(cond,f);
    @endcode

    is similar to:

    @code
    T r = cond ? Allbits : f;
    @endcode

    @par Alias:
    @c if_nan_else,

    @see genmask, Allbits, Nan

  **/
  Value if_allbits_else(Value const& c, Value const& f);

  //@overload
  Value if_allbits_else(LogicalValue const& c, Value const& f);
} }
#endif

#include <boost/simd/function/scalar/if_allbits_else.hpp>
#include <boost/simd/function/simd/if_allbits_else.hpp>

#endif

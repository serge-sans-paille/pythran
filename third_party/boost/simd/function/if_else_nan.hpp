//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_ELSE_NAN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_ELSE_NAN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-boolean
    This function object conditionally returns @c x (respectively @ref Nan)
    if @c c is @ref True (respectively  @ref False)

    This is an alias of @ref if_else_allbits



    @par Header <boost/simd/function/if_else_nan.hpp>

    @par Example:

      @snippet if_else_nan.cpp if_else_nan

    @par Possible output:

      @snippet if_else_nan.txt if_else_nan

  **/
  Value1 if_else_nan(Value0 const& c, Value1 const& x);
} }
#endif

#include <boost/simd/function/scalar/if_else_allbits.hpp>
#include <boost/simd/function/simd/if_else_nan.hpp>

#endif

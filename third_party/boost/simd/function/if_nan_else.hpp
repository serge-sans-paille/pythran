//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IF_NAN_ELSE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IF_NAN_ELSE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing if_nan_else capabilities

    If cond is @ref True returns @ref Allbits else returns f

    This is a convenience alias of @ref if_allbits_else
  **/
  Value if_nan_else(Value const& r, Value const& v0);

  //@overload
  Value if_nan_else(LogicalValue const& r, Value const& v0);
} }
#endif

#include <boost/simd/function/scalar/if_allbits_else.hpp>
#include <boost/simd/function/simd/if_nan_else.hpp>

#endif

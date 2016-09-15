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
    Function object implementing if_else_nan capabilities

    If cond is @ref True returns t else returns allbits

    This is a convenience alias of @ref if_else_allbits
  **/
  Value if_else_nan(Value const& c, Value const& v0);

  //@overload
  Value if_else_nan(LogicalValue const& c, Value const& v0);
} }
#endif

#include <boost/simd/function/scalar/if_else_allbits.hpp>
#include <boost/simd/function/simd/if_else_nan.hpp>

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_IF_ELSE_NAN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_IF_ELSE_NAN_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/function/definition/if_else_allbits.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    using if_else_nan_ = if_else_allbits_;
  }

  BOOST_DISPATCH_CALLABLE_DEFINITION(tag::if_else_nan_,if_else_nan);
} }

#endif

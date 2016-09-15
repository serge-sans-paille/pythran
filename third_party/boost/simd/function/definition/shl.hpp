//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_SHL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_SHL_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/function/definition/shift_left.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    using shl_ = shift_left_;
  }

  BOOST_DISPATCH_CALLABLE_DEFINITION(tag::shl_,shl);
} }

#endif

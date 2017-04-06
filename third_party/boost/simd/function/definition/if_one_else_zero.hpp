//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_IF_ONE_ELSE_ZERO_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, if_one_else_zero_, boost::dispatch::elementwise_<if_one_else_zero_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, if_one_else_zero_)
  }

  BOOST_DISPATCH_CALLABLE_DEFINITION(tag::if_one_else_zero_,if_one_else_zero);


} }

#endif

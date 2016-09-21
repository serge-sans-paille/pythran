//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_SPLATTED_MINIMUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_SPLATTED_MINIMUM_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, splatted_minimum_, boost::dispatch::elementwise_<splatted_minimum_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, splatted_minimum_);
  }

  BOOST_DISPATCH_CALLABLE_DEFINITION(tag::splatted_minimum_,splatted_minimum);


} }

#endif

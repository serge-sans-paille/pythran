//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, bitwise_cast_, boost::dispatch::elementwise_<bitwise_cast_>);
  }
  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, bitwise_cast_)
  }
  namespace functional
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::bitwise_cast_,bitwise_cast);
  }

  template < typename Target,  typename Arg > BOOST_FORCEINLINE
  Target bitwise_cast(Arg&& a0) BOOST_NOEXCEPT
  {
    return functional::bitwise_cast(std::forward<Arg>(a0), boost::dispatch::as_<Target>{});
  }
} }

#endif

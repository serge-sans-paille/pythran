//==================================================================================================
/*
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_PACK_CAST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_PACK_CAST_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/detail/dispatch.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, pack_cast_, boost::dispatch::elementwise_<pack_cast_>);
  }
  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, pack_cast_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::pack_cast_,pack_cast_impl);
  }

  template<typename Target, typename Arg>
  BOOST_FORCEINLINE auto pack_cast(Arg const& a0) BOOST_NOEXCEPT
    -> decltype(detail::pack_cast_impl(a0, boost::dispatch::as_<Target>{}))
  {
    return detail::pack_cast_impl(a0, boost::dispatch::as_<Target>{});
  }
} }

#endif

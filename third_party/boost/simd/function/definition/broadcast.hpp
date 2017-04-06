//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DEFINITION_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DEFINITION_BROADCAST_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    BOOST_DISPATCH_MAKE_TAG(ext, broadcast_, boost::dispatch::unspecified_<broadcast_>);
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, broadcast_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::broadcast_,broadcast);
  }

  template < int N, typename T> BOOST_FORCEINLINE T broadcast(const T& a) BOOST_NOEXCEPT
  {
    return detail::broadcast(a, nsm::int32_t<N>());
  }
} }

#endif

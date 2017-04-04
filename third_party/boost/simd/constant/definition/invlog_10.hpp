//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_INVLOG_10_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_INVLOG_10_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct invlog_10_ : boost::dispatch::constant_value_<invlog_10_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,invlog_10_,boost::dispatch::constant_value_<invlog_10_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x3ede5bd9UL, 0x3fdbcb7b1526e50eULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, invlog_10_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::invlog_10_,invlog_10);
  }

  template<typename T> BOOST_FORCEINLINE auto Invlog_10()
  BOOST_NOEXCEPT_DECLTYPE(detail::invlog_10( boost::dispatch::as_<T>{}))
  {
    return detail::invlog_10( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Invlog_10(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Invlog_10<T>())
  {
    return Invlog_10<T>();
  }
} }

#endif

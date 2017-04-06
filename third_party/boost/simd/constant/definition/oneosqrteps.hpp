//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_ONEOSQRTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_ONEOSQRTEPS_HPP_INCLUDED

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
    struct oneosqrteps_ : boost::dispatch::constant_value_<oneosqrteps_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,oneosqrteps_,boost::dispatch::constant_value_<oneosqrteps_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0x453504f3UL, 0x4190000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, oneosqrteps_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::oneosqrteps_,oneosqrteps);
  }

  template<typename T> BOOST_FORCEINLINE auto Oneosqrteps()
  BOOST_NOEXCEPT_DECLTYPE(detail::oneosqrteps( boost::dispatch::as_<T>{}))
  {
    return detail::oneosqrteps( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Oneosqrteps(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Oneosqrteps<T>())
  {
    return Oneosqrteps<T>();
  }
} }

#endif

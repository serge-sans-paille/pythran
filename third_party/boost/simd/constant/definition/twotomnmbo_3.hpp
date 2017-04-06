//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_TWOTOMNMBO_3_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_TWOTOMNMBO_3_HPP_INCLUDED

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
    struct twotomnmbo_3_ : boost::dispatch::constant_value_<twotomnmbo_3_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,twotomnmbo_3_,boost::dispatch::constant_value_<twotomnmbo_3_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x3ba14518LL, 0x3ed428a2f98d7286ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, twotomnmbo_3_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::twotomnmbo_3_,twotomnmbo_3);
  }

  template<typename T> BOOST_FORCEINLINE auto Twotomnmbo_3()
  BOOST_NOEXCEPT_DECLTYPE(detail::twotomnmbo_3( boost::dispatch::as_<T>{}))
  {
    return detail::twotomnmbo_3( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Twotomnmbo_3(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Twotomnmbo_3<T>())
  {
    return Twotomnmbo_3<T>();
  }
} }

#endif

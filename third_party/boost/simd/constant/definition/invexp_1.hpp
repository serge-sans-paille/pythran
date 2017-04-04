//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_INVEXP_1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_INVEXP_1_HPP_INCLUDED

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
    struct invexp_1_ : boost::dispatch::constant_value_<invexp_1_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,invexp_1_,boost::dispatch::constant_value_<invexp_1_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x3ebc5ab2UL, 0x3fd78b56362cef38ull);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, invexp_1_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::invexp_1_,invexp_1);
  }

  template<typename T> BOOST_FORCEINLINE auto Invexp_1()
  BOOST_NOEXCEPT_DECLTYPE(detail::invexp_1( boost::dispatch::as_<T>{}))
  {
    return detail::invexp_1( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Invexp_1(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Invexp_1<T>())
  {
    return Invexp_1<T>();
  }
} }

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_INV2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_INV2PI_HPP_INCLUDED

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
    struct inv2pi_ : boost::dispatch::constant_value_<inv2pi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,inv2pi_,boost::dispatch::constant_value_<inv2pi_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X3E22F983, 0X3FC45F306DC9C883LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, inv2pi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::inv2pi_,inv2pi);
  }

  template<typename T> BOOST_FORCEINLINE auto Inv2pi()
  BOOST_NOEXCEPT_DECLTYPE(detail::inv2pi( boost::dispatch::as_<T>{}))
  {
    return detail::inv2pi( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Inv2pi(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Inv2pi<T>())
  {
    return Inv2pi<T>();
  }
} }

#endif

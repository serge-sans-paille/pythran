//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MONE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MONE_HPP_INCLUDED

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
    struct mone_ : boost::dispatch::constant_value_<mone_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mone_,boost::dispatch::constant_value_<mone_>);
      BOOST_SIMD_REGISTER_CONSTANT(-1, 0xbf800000UL, 0xbff0000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mone_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mone_,mone);
  }

  template<typename T> BOOST_FORCEINLINE auto Mone()
  BOOST_NOEXCEPT_DECLTYPE(detail::mone( boost::dispatch::as_<T>{}))
  {
    return detail::mone( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Mone(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Mone<T>())
  {
    return Mone<T>();
  }
} }

#endif

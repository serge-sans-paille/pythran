//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MTWO_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MTWO_HPP_INCLUDED

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
    struct mtwo_ : boost::dispatch::constant_value_<mtwo_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mtwo_,boost::dispatch::constant_value_<mtwo_>);
      BOOST_SIMD_REGISTER_CONSTANT(-2, 0xc0000000UL, 0xc000000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mtwo_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mtwo_,mtwo);
  }

  template<typename T> BOOST_FORCEINLINE auto Mtwo()
  BOOST_NOEXCEPT_DECLTYPE(detail::mtwo( boost::dispatch::as_<T>{}))
  {
    return detail::mtwo( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Mtwo(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Mtwo<T>())
  {
    return Mtwo<T>();
  }
} }

#endif

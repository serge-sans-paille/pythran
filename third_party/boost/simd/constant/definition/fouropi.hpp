//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_FOUROPI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_FOUROPI_HPP_INCLUDED

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
    struct fouropi_ : boost::dispatch::constant_value_<fouropi_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,fouropi_,boost::dispatch::constant_value_<fouropi_>);
      BOOST_SIMD_REGISTER_CONSTANT(1, 0X3FA2F983, 0X3FF45F306DC9C883LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, fouropi_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::fouropi_,fouropi);
  }

  template<typename T> BOOST_FORCEINLINE auto Fouropi()
  BOOST_NOEXCEPT_DECLTYPE(detail::fouropi( boost::dispatch::as_<T>{}))
  {
    return detail::fouropi( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Fouropi(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Fouropi<T>())
  {
    return Fouropi<T>();
  }
} }

#endif

//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_TWOPIO_3_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_TWOPIO_3_HPP_INCLUDED

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
    struct twopio_3_ : boost::dispatch::constant_value_<twopio_3_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,twopio_3_,boost::dispatch::constant_value_<twopio_3_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0X40060A92LL, 0X4000C152382D7366ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, twopio_3_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::twopio_3_,twopio_3);
  }

  template<typename T> BOOST_FORCEINLINE auto Twopio_3()
  BOOST_NOEXCEPT_DECLTYPE(detail::twopio_3( boost::dispatch::as_<T>{}))
  {
    return detail::twopio_3( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Twopio_3(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Twopio_3<T>())
  {
    return Twopio_3<T>();
  }
} }

#endif

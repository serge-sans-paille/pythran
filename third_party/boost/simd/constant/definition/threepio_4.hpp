//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_THREEPIO_4_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_THREEPIO_4_HPP_INCLUDED

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
    struct threepio_4_ : boost::dispatch::constant_value_<threepio_4_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,threepio_4_,boost::dispatch::constant_value_<threepio_4_>);
      BOOST_SIMD_REGISTER_CONSTANT(2, 0X4016CBE4, 0X4002D97C7F3321D2LL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, threepio_4_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::threepio_4_,threepio_4);
  }

  template<typename T> BOOST_FORCEINLINE auto Threepio_4()
  BOOST_NOEXCEPT_DECLTYPE(detail::threepio_4( boost::dispatch::as_<T>{}))
  {
    return detail::threepio_4( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Threepio_4(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Threepio_4<T>())
  {
    return Threepio_4<T>();
  }
} }

#endif

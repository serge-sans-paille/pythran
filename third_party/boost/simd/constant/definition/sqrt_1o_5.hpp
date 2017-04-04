//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_SQRT_1O_5_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_SQRT_1O_5_HPP_INCLUDED

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
    struct sqrt_1o_5_ : boost::dispatch::constant_value_<sqrt_1o_5_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,sqrt_1o_5_,boost::dispatch::constant_value_<sqrt_1o_5_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0x3ee4f92eUL, 0x3fdc9f25c5bfedd9ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, sqrt_1o_5_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::sqrt_1o_5_,sqrt_1o_5);
  }

  template<typename T> BOOST_FORCEINLINE auto Sqrt_1o_5()
  BOOST_NOEXCEPT_DECLTYPE(detail::sqrt_1o_5( boost::dispatch::as_<T>{}))
  {
    return detail::sqrt_1o_5( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Sqrt_1o_5(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Sqrt_1o_5<T>())
  {
    return Sqrt_1o_5<T>();
  }
} }

#endif

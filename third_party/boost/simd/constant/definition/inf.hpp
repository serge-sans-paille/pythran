//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_INF_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_INF_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch.hpp>
#include <boost/simd/detail/constant_traits.hpp>
#include <boost/simd/constant/definition/valmax.hpp>
#include <boost/simd/detail/dispatch/function/make_callable.hpp>
#include <boost/simd/detail/dispatch/hierarchy/functions.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct inf_ : boost::dispatch::constant_value_<inf_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,inf_,boost::dispatch::constant_value_<inf_>);

      struct value_map
      {
        template<typename X>
        static auto value(X const& x) -> decltype(valmax_::value_map::value(x));

        template<typename X>
        static nsm::single_<0x7F800000U> value(boost::dispatch::single_<X> const&);

        template<typename X>
        static nsm::double_<0x7FF0000000000000ULL> value(boost::dispatch::double_<X> const&);
      };
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, inf_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::inf_,inf);
  }

  template<typename T> BOOST_FORCEINLINE auto Inf()
  -> decltype(detail::inf(boost::dispatch::as_<T>{}))
  {
    return detail::inf( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Inf(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Inf<T>())
  {
    return Inf<T>();
  }
} }

#endif


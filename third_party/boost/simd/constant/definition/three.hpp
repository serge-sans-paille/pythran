//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_THREE_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_THREE_HPP_INCLUDED

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
    struct three_ : boost::dispatch::constant_value_<three_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,three_,boost::dispatch::constant_value_<three_>);
      BOOST_SIMD_REGISTER_CONSTANT(3, 0x40400000UL, 0x4008000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, three_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::three_,three);
  }

  template<typename T> BOOST_FORCEINLINE auto Three()
  BOOST_NOEXCEPT_DECLTYPE(detail::three( boost::dispatch::as_<T>{}))
  {
    return detail::three( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Three(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Three<T>())
  {
    return Three<T>();
  }
} }

#endif

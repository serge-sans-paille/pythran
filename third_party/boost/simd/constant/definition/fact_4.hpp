//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_FACT_4_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_FACT_4_HPP_INCLUDED

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
    struct fact_4_ : boost::dispatch::constant_value_<fact_4_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,fact_4_,boost::dispatch::constant_value_<fact_4_>);
      BOOST_SIMD_REGISTER_CONSTANT(24, 0x41c00000U, 0x4038000000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, fact_4_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::fact_4_,fact_4);
  }

  template<typename T> BOOST_FORCEINLINE auto Fact_4()
  BOOST_NOEXCEPT_DECLTYPE(detail::fact_4( boost::dispatch::as_<T>{}))
  {
    return detail::fact_4( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Fact_4(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Fact_4<T>())
  {
    return Fact_4<T>();
  }
} }

#endif

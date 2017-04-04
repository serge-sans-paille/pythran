//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_FACT_9_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_FACT_9_HPP_INCLUDED

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
    struct fact_9_ : boost::dispatch::constant_value_<fact_9_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,fact_9_,boost::dispatch::constant_value_<fact_9_>);
      BOOST_SIMD_REGISTER_CONSTANT(362880, 0x48b13000U,0x4116260000000000ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, fact_9_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::fact_9_,fact_9);
  }

  template<typename T> BOOST_FORCEINLINE auto Fact_9()
  BOOST_NOEXCEPT_DECLTYPE(detail::fact_9( boost::dispatch::as_<T>{}))
  {
    return detail::fact_9( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Fact_9(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Fact_9<T>())
  {
    return Fact_9<T>();
  }
} }

#endif

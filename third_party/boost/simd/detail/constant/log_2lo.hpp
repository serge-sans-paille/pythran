//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_CONSTANT_LOG_2LO_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_CONSTANT_LOG_2LO_HPP_INCLUDED

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
    struct log_2lo_ : boost::dispatch::constant_value_<log_2lo_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,log_2lo_,boost::dispatch::constant_value_<log_2lo_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xb95e8083UL, 0x3dea39ef35793c76ULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, log_2lo_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::log_2lo_,log_2lo);
  }

  template<typename T> BOOST_FORCEINLINE auto Log_2lo()
  BOOST_NOEXCEPT_DECLTYPE(detail::log_2lo( boost::dispatch::as_<T>{}))
  {
    return detail::log_2lo( boost::dispatch::as_<T>{} );
  }
} }

#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif

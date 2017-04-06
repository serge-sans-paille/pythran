//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MLOG2TWO2NMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MLOG2TWO2NMB_HPP_INCLUDED

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
    struct mlog2two2nmb_ : boost::dispatch::constant_value_<mlog2two2nmb_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mlog2two2nmb_,boost::dispatch::constant_value_<mlog2two2nmb_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xc1b80000UL, 0xc04a000000000000ULL); //was C04A8 ?
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mlog2two2nmb_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mlog2two2nmb_,mlog2two2nmb);
  }

  template<typename T> BOOST_FORCEINLINE auto Mlog2two2nmb()
  BOOST_NOEXCEPT_DECLTYPE(detail::mlog2two2nmb( boost::dispatch::as_<T>{}))
  {
    return detail::mlog2two2nmb( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Mlog2two2nmb(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Mlog2two2nmb<T>())
  {
    return Mlog2two2nmb<T>();
  }
} }

#endif

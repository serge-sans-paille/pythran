//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MLOGTWO2NMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MLOGTWO2NMB_HPP_INCLUDED

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
    struct mlogtwo2nmb_ : boost::dispatch::constant_value_<mlogtwo2nmb_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mlogtwo2nmb_,boost::dispatch::constant_value_<mlogtwo2nmb_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0XC17F1402UL, 0XC04205966F2B4F12ULL); //c0425e4f7b2737faULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mlogtwo2nmb_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mlogtwo2nmb_,mlogtwo2nmb);
  }

  template<typename T> BOOST_FORCEINLINE auto Mlogtwo2nmb()
  BOOST_NOEXCEPT_DECLTYPE(detail::mlogtwo2nmb( boost::dispatch::as_<T>{}))
  {
    return detail::mlogtwo2nmb( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Mlogtwo2nmb(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Mlogtwo2nmb<T>())
  {
    return Mlogtwo2nmb<T>();
  }
} }

#endif

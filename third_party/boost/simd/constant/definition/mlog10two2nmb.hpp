//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEFINITION_MLOG10TWO2NMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEFINITION_MLOG10TWO2NMB_HPP_INCLUDED

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
    struct mlog10two2nmb_ : boost::dispatch::constant_value_<mlog10two2nmb_>
    {
      BOOST_DISPATCH_MAKE_CALLABLE(ext,mlog10two2nmb_,boost::dispatch::constant_value_<mlog10two2nmb_>);
      BOOST_SIMD_REGISTER_CONSTANT(0, 0xc0dd8edeUL, 0xc02fe8bffd88220eULL);
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_FUNCTION_DECLARATION(tag, mlog10two2nmb_)
  }

  namespace detail
  {
    BOOST_DISPATCH_CALLABLE_DEFINITION(tag::mlog10two2nmb_,mlog10two2nmb);
  }

  template<typename T> BOOST_FORCEINLINE auto Mlog10two2nmb()
  BOOST_NOEXCEPT_DECLTYPE(detail::mlog10two2nmb( boost::dispatch::as_<T>{}))
  {
    return detail::mlog10two2nmb( boost::dispatch::as_<T>{} );
  }

  template<typename T> BOOST_FORCEINLINE
  auto Mlog10two2nmb(boost::dispatch::as_<T> const&) BOOST_NOEXCEPT_DECLTYPE(Mlog10two2nmb<T>())
  {
    return Mlog10two2nmb<T>();
  }
} }

#endif

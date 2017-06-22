//==================================================================================================
/*!
  @file

  Defines the apply_sign meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_APPLY_SIGN_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_APPLY_SIGN_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#include <boost/simd/detail/dispatch/meta/as_signed.hpp>

namespace boost { namespace dispatch
{
  namespace detail
  {
    template<typename T,typename Sign> struct apply_sign;
    template<typename T> struct apply_sign<T,signed> : boost::dispatch::as_signed<T>      {};
    template<typename T> struct apply_sign<T,unsigned> : boost::dispatch::as_unsigned<T>  {};
  }

  /*!
    @ingroup group-generation
    @brief Apply sign to given type

    Transforms any type @c T into a corresponding type with specified sign @c Sign.

    @tparam T     Type to modify
    @tparam Sign  Sign to apply to @c T
  **/
  template<typename T,typename Sign> struct apply_sign : detail::apply_sign<T,Sign> {};

  /*!
    @ingroup group-generation
    Eager short-cut to boost::dispatch::apply_sign
  **/
  template<typename T,typename Sign> using apply_sign_t = typename apply_sign<T,Sign>::type;
} }

#endif

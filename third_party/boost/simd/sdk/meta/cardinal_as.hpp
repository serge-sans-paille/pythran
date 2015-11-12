//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_CARDINAL_AS_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_CARDINAL_AS_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/dispatch/meta/na.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/utility/enable_if.hpp>

/* WKRD: for some unknown reason, MSVC seems to require this even if
 * cardinal_as isn't instantiated */
#include <boost/simd/sdk/simd/details/native/meta/cardinal_of_declare.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    template<class T, class X, class U>
    struct cardinal_as
         : meta::cardinal_of< native<T,X> >
    {
    };

    template<class T, class X>
    struct cardinal_as<T, X, dispatch::meta::na_>
         : mpl::size_t<1>
    {
    };
  }

  namespace meta
  {
    template<class T, class X, class Enable = void>
    struct cardinal_as : details::cardinal_as<T, X, typename as_simd<T, X>::type>
    {};

    template<class T, class X>
    struct cardinal_as<T, X, typename enable_if< fusion::traits::is_sequence<T> >::type>
         : meta::cardinal_of< native<T, X> >
    {
    };
  }
} }

#endif

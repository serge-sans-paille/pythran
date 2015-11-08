//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_EXTENSION_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_EXTENSION_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions/meta/tags.hpp>
#include <boost/simd/forward/aligned_array.hpp>
#include <boost/dispatch/meta/na.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T,class Dummy=void, class Dummy1 = void>
  struct extension_of
  {
    typedef dispatch::meta::na_ type;
  };

  template<class T, class X>
  struct extension_of< boost::simd::native<T,X> > { typedef X type; };

  template<class T, class N, std::size_t Align>
  struct extension_of< boost::simd::aligned_array<T, N::value, Align>, T, N>
  {
    typedef tag::simd_emulation_< N::value * sizeof(T) > type;
  };
} } }


#endif

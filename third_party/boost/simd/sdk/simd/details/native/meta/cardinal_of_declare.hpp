//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_CARDINAL_OF_DECLARE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_CARDINAL_OF_DECLARE_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd
{

namespace details
{
  template<class T, class X, bool B = false>
  struct cardinal_of_native;
}

namespace meta
{
  ////////////////////////////////////////////////////////////////////////////
  // Overload for SIMD native types
  ////////////////////////////////////////////////////////////////////////////
  template<class T, class X>
  struct  cardinal_of< native<T,X> >
       :  details::cardinal_of_native<T, X, boost::fusion::traits::is_sequence<T>::value>
  {};
} } }

#endif


//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_CARDINAL_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_CARDINAL_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/details/native/meta/cardinal_of_declare.hpp>
#include <boost/simd/sdk/meta/cardinal_as.hpp>
#include <boost/simd/sdk/simd/details/max_value.hpp>
#include <boost/mpl/size_t.hpp>

namespace boost { namespace simd { namespace details
{
  template<class T, class X, bool B>
  struct cardinal_of_native
       : boost::mpl::size_t< sizeof(typename meta::as_simd<T, X>::type)/sizeof(T) >
  {
  };

  template<class T, class X>
  struct cardinal_of_native<T, X, true>
       : meta::cardinal_of< native< typename max_value< T, meta::cardinal_as<mpl::_, X> >::type
                                  , X
                                  >
                          >
  {
  };

} } }

#endif

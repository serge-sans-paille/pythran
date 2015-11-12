//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_IS_VECTORIZABLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_IS_VECTORIZABLE_HPP_INCLUDED

#include <boost/dispatch/meta/na.hpp>
#include <boost/dispatch/meta/all.hpp>
#include <boost/simd/sdk/simd/meta/as_simd.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace simd { namespace details
{
  /// INTERNAL ONLY
  template<class T, class Extension, class Enable = void>
  struct  is_vectorizable
        : boost::mpl::bool_ < ! boost::is_same
                                < typename meta::as_simd<T,Extension>::type
                                , boost::dispatch::meta::na_
                                >::value
                            >
  {};

  /// INTERNAL ONLY
  template< class T, class Extension >
  struct  is_vectorizable < T
                          , Extension
                          , typename
                            boost::enable_if< boost::fusion::traits
                                                   ::is_sequence<T>
                                            >::type
                          >
        : boost::dispatch::meta
               ::all_seq< is_vectorizable<boost::mpl::_, Extension>
                        , typename boost::fusion::result_of::as_vector<T>::type
                        >
  {};
} } }

namespace boost { namespace simd { namespace meta
{
  template<class T,class Extension>
  struct is_vectorizable
       : details::is_vectorizable<T,Extension>
  {};
} } }

#endif

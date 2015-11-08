//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_PACK_META_MODEL_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_META_MODEL_OF_HPP_INCLUDED

#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/simd/sdk/simd/details/max_value.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template< class T
          , std::size_t N
          >
  struct model_of< boost::simd::pack<T, N> >
  {
    struct type
    {
      template<class X>
      struct apply
      {
        typedef typename boost::dispatch::meta::primitive_of< typename simd::details::max_value_noseq<T, mpl::sizeof_<mpl::_> >::type>::type TT;
        typedef typename boost::dispatch::meta::primitive_of< typename simd::details::max_value_noseq<X, mpl::sizeof_<mpl::_> >::type>::type XX;

        typedef boost::simd::pack< X
                                 , sizeof(typename boost::simd::pack<TT, N>::data_type::native_type) / sizeof(XX)
                                 > type;
      };
    };
  };
} } }

#endif

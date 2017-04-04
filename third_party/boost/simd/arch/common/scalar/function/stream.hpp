//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_STREAM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_STREAM_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/config.hpp>
#include <boost/simd/function/aligned_store.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/include/sequence.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  /// INTERNAL ONLY - Scalar stream and store are equivalent
  BOOST_DISPATCH_OVERLOAD ( stream_
                          , (typename A0 , typename A1 , typename A2)
                          , bd::cpu_
                          , bd::unspecified_<A0>
                          , bd::input_iterator_< bd::scalar_< bd::unspecified_<A1> > >
                          , bd::scalar_< bd::integer_<A2> >
                          )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1, A2 a2) const
    {
      boost::simd::aligned_store(a0,a1,a2);
    }
  };

  /// INTERNAL ONLY - Scalar stream and store are equivalent
  BOOST_DISPATCH_OVERLOAD ( stream_
                          , (typename A0 , typename A1)
                          , bd::cpu_
                          , bd::unspecified_<A0>
                          , bd::input_iterator_< bd::scalar_< bd::unspecified_<A1> > >
                          )
  {

    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      boost::simd::aligned_store(a0,a1);
    }
  };

//  /// INTERNAL ONLY - Fusion sequence stream with offset
//  BOOST_DISPATCH_OVERLOAD ( stream_
//                          , (typename A0 , typename A1 , typename A2)
//                          , bd::cpu_
//                          , fusion_sequence_<A0>
//                          , fusion_sequence_<A1>
//                          , bd::scalar_< bd::integer_<A2> >
//                          )
//  {
//    typedef void result_type;
//
//    BOOST_FORCEINLINE result_type
//    operator()(A0 const& a0, A1 const& a1, A2 a2) const
//    {
//      meta::iterate < fusion::result_of::size<A1>::type::value>
//                    ( details::storer < boost::simd::
//                                        tag::stream_(A0, A1, A2)
//                                      >(a0, a1, a2)
//                    );
//    }
//  };
//
//  /// INTERNAL ONLY - Fusion sequence stream without offset
//  BOOST_DISPATCH_OVERLOAD ( stream_
//                          , (typename A0 , typename A1)
//                          , bd::cpu_
//                          , fusion_sequence_<A0>
//                          , fusion_sequence_<A1>
//                          )
//  {
//    typedef void result_type;
//
//    BOOST_FORCEINLINE result_type
//    operator()(A0 const& a0, A1 const& a1) const
//    {
//      meta::iterate < fusion::result_of::size<A1>::type::value>
//                    ( details::storer < boost::simd::
//                                        tag::stream_(A0, A1)
//                                      >(a0, a1)
//                    );
//    }
//  };
} } }

#endif

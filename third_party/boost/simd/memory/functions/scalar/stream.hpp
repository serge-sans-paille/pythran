//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_STREAM_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_STREAM_HPP_INCLUDED

#include <boost/simd/memory/functions/stream.hpp>
#include <boost/simd/memory/functions/scalar/aligned_store.hpp>
#include <boost/simd/memory/functions/details/store.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Scalar stream and store are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (unspecified_<A0>)
                                      (iterator_< scalar_< unspecified_<A1> > >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1, A2 a2) const
    {
      boost::simd::aligned_store(a0,a1,a2);
    }
  };

  /// INTERNAL ONLY - Scalar stream and store are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (unspecified_<A0>)
                                      (iterator_< scalar_< unspecified_<A1> > >)
                                    )
  {

    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      boost::simd::aligned_store(a0,a1);
    }
  };

  /// INTERNAL ONLY - Fusion sequence stream with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_, tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (fusion_sequence_<A0>)
                                      (fusion_sequence_<A1>)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1, A2 a2) const
    {
      meta::iterate < fusion::result_of::size<A1>::type::value>
                    ( details::storer < boost::simd::
                                        tag::stream_(A0, A1, A2)
                                      >(a0, a1, a2)
                    );
    }
  };

  /// INTERNAL ONLY - Fusion sequence stream without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_, tag::cpu_
                                    , (A0)(A1)
                                    , (fusion_sequence_<A0>)
                                      (fusion_sequence_<A1>)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1) const
    {
      meta::iterate < fusion::result_of::size<A1>::type::value>
                    ( details::storer < boost::simd::
                                        tag::stream_(A0, A1)
                                      >(a0, a1)
                    );
    }
  };
} } }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_SSE2_STREAM_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_SSE2_STREAM_HPP_INCLUDED
#if defined(BOOST_SIMD_HAS_SSE2_SUPPORT)

#include <boost/simd/memory/functions/stream.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Integer stream with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_, tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (scalar_< ints32_<A0> >)
                                      (iterator_< scalar_< unspecified_<A1> > >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 a1, A2 a2) const
    {
      _mm_stream_si32(reinterpret_cast<int*>(a1+a2), static_cast<int>(a0));
    }
  };

  /// INTERNAL ONLY - Integer stream without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< ints32_<A0> >)
                                      (iterator_< scalar_< unspecified_<A1> > >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 a1) const
    {
      _mm_stream_si32(reinterpret_cast<int*>(a1), static_cast<int>(a0));
    }
  };
} } }

#endif
#endif

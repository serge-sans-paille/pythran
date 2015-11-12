//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_STREAM_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_STREAM_HPP_INCLUDED

#include <boost/simd/memory/functions/stream.hpp>
#include <boost/simd/include/functions/simd/aligned_store.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - If no stream intrinsic, do a classical store.
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (iterator_< scalar_< unspecified_<A1> > >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      boost::simd::aligned_store(a0, a1, a2);
    }
  };
} } }

#endif

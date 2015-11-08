//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_STREAM_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_STREAM_HPP_INCLUDED

#include <boost/simd/include/functions/stream.hpp>
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY pack stream with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (iterator_< scalar_< fundamental_<A1> > >)
                                      (generic_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      boost::simd::stream(evaluate(a0),a1,a2);
    }
  };

  /// INTERNAL ONLY pack stream without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::stream_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (iterator_< scalar_< fundamental_<A1> > >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      boost::simd::stream(evaluate(a0),a1);
    }
  };
} } }

#endif

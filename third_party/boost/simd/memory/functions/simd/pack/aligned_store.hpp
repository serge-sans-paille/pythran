//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014                 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/include/functions/aligned_store.hpp>
#include <boost/simd/include/functions/evaluate.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY pack store with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 a2) const
    {
      boost::simd::aligned_store(evaluate(a0),a1,a2);
    }
  };

  /// INTERNAL ONLY mask pack store with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)(X)(Tag)(Arity)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                      ((expr_ < simd_< logical_<A3>, X >
                                              , Tag, Arity
                                              >
                                      ))
                                    )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 const& a2, A3 const& a3) const
    {
      boost::simd::aligned_store(evaluate(a0),a1,a2,evaluate(a3));
    }
  };

  /// INTERNAL ONLY pack scatter
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (iterator_< unspecified_<A1> >)
                                      ((simd_< integer_<A2>, X >))
                                    )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      boost::simd::aligned_store(evaluate(a0),a1,a2);
    }
  };

  /// INTERNAL ONLY mask pack scatter
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)(X)(Tag)(Arity)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (iterator_< unspecified_<A1> >)
                                      ((simd_< integer_<A2>, X >))
                                      ((expr_ < simd_< logical_<A3>, X >
                                              , Tag, Arity
                                              >
                                      ))
                                    )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 a1, A2 const& a2, A3 const& a3) const
    {
      boost::simd::aligned_store(evaluate(a0),a1,a2,evaluate(a3));
    }
  };

  /// INTERNAL ONLY pack store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (iterator_< unspecified_<A1> >)
                                    )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1) const
    {
      boost::simd::aligned_store(evaluate(a0),a1);
    }
  };

  /// INTERNAL ONLY mask pack store without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)(Tag)(Arity)
                                    , ((ast_<A0, boost::simd::domain>))
                                      (iterator_< unspecified_<A1> >)
                                      ((expr_ < simd_< logical_<A2>, X >
                                              , Tag, Arity
                                              >
                                      ))
                                    )
  {
    typedef void  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      boost::simd::aligned_store(evaluate(a0),a1,evaluate(a2));
    }
  };
} } }

#endif

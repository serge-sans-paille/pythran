//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_LOAD_HPP_INCLUDED

#include <boost/simd/memory/functions/load.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/simd/memory/functions/details/load.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (iterator_< unspecified_<A0> >)
                                      (target_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, A2 a2) const
    {
      return load<result_type>(a0+a2);
    }
  };

  /// INTERNAL ONLY - masked scalar load offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)(A4)
                                    , (iterator_< unspecified_<A0> >)
                                      (target_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                      (scalar_< fundamental_<A3> >)
                                      (unspecified_<A4>)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, A2 a2, A3 const& a3, A4 const& a4 ) const
    {
      return load<result_type>(a0+a2,a3,a4);
    }
  };

  /// INTERNAL ONLY - masked scalar load offset, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)
                                    , (iterator_< unspecified_<A0> >)
                                      (target_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                      (scalar_< fundamental_<A3> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, A2 a2, A3 const& a3 ) const
    {
      return load<result_type>(a0+a2,a3,result_type(0));
    }
  };

  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (iterator_< unspecified_<A0> >)
                                      (target_< unspecified_<A1> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&) const { return *a0; }
  };

  /// INTERNAL ONLY - masked scalar load, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (iterator_< unspecified_<A0> >)
                                      (target_< unspecified_<A1> >)
                                      (scalar_< fundamental_<A2> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, A2 const& a2 ) const
    {
      return load<result_type>(a0,a2,result_type(0));
    }
  };

  /// INTERNAL ONLY - masked scalar load
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)
                                    , (iterator_< unspecified_<A0> >)
                                      (target_< unspecified_<A1> >)
                                      (scalar_< fundamental_<A2> >)
                                      (scalar_< unspecified_<A3> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, A2 const& a2, A3 const& a3 ) const
    {
      return (a2 ? *a0 : a3);
    }
  };

  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (fusion_sequence_<A0>)
                                      ((target_< fusion_sequence_<A1> >))
                                      (generic_< integer_<A2> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const&, A2 const& a2) const
    {
      result_type that;
      meta::iterate < fusion::result_of::size<A0>::type::value>
                    ( details::loader < boost::simd::
                                        tag::load_(A0, result_type, A2)
                                      >(a0, that, a2)
                    );
      return that;
    }
  };

  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)
                                    , (fusion_sequence_<A0>)
                                      ((target_< fusion_sequence_<A2> >))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A2 const&) const
    {
      result_type that;
      meta::iterate < fusion::result_of::size<A0>::type::value>
                    ( details::loader < boost::simd::
                                        tag::load_(A0, result_type)
                                      >(a0, that)
                    );
      return that;
    }
  };

  /// INTERNAL ONLY - Load through pointer of fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_
                                      , tag::cpu_
                                      , (A0)(A1)(A2)
                                      , (mpl::not_< simd::meta::is_native<typename A1::type> >)
                                      , (iterator_< fusion_sequence_<A0> >)
                                        (target_< fusion_sequence_<A1> >)
                                        (scalar_< integer_<A2> >)
                                      )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&, const A2& a2) const
    {
      result_type that;

      static const int N = fusion::result_of::size<result_type>::type::value;
      meta::iterate<N>( details::inserter<A0,result_type,A2>(a0,that,a2) );

      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_
                                      , tag::cpu_
                                      , (A0)(A2)
                                      , (mpl::not_< simd::meta::is_native<typename A2::type> >)
                                      , (iterator_< fusion_sequence_<A0> >)
                                        (target_< fusion_sequence_<A2> >)
                                      )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A2&) const
    {
      result_type that;

      static const int N = fusion::result_of::size<result_type>::type::value;
      meta::iterate<N>( details::inserter<A0,result_type>(a0,that) );

      return that;
    }
  };
} } }

#endif

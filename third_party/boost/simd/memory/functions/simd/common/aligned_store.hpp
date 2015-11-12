//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/memory/functions/aligned_store.hpp>
#include <boost/simd/memory/functions/details/store.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/include/functions/simd/store.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/mpl/equal_to.hpp>
#include <iterator>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - mask Regular offset SIMD store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 a1, A2 a2, A3 const& a3) const
    {
      boost::simd::aligned_store(a0, a1+a2, a3);
    }
  };

  /// INTERNAL ONLY - Regular offset SIMD store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (iterator_< unspecified_<A1> >)
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 a1, A2 a2) const
    {
      boost::simd::aligned_store(a0, a1+a2);
    }
  };

  /// INTERNAL ONLY - masked Regular SIMD store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((simd_<arithmetic_<A0>, X >))
                                      (iterator_< scalar_< arithmetic_<A1> > >)
                                      ((simd_< logical_<A2>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a1, A0, typename std::iterator_traits<A1>::value_type);
      boost::simd::store(a0, a1, a2);
    }
  };

  /// INTERNAL ONLY - Regular SIMD store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_<arithmetic_<A0>, X >))
                                      (iterator_< scalar_< arithmetic_<A1> > >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 a1) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a1, A0, typename std::iterator_traits<A1>::value_type);
      boost::simd::store(a0, a1);
    }
  };

  /// INTERNAL ONLY - Masked Scatter SIMD store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::aligned_store_, tag::cpu_
                                       , (A0)(A1)(A2)(A3)(X)(Y)
                                       , (mpl::equal_to
                                            < boost::simd::meta::cardinal_of<A0>
                                            , boost::simd::meta::cardinal_of<A2>
                                            >
                                         )
                                       , ((simd_< unspecified_<A0>, X >))
                                         (iterator_< unspecified_<A1>  >)
                                         ((simd_< integer_<A2>, Y >))
                                         ((simd_< logical_<A3>
                                                   , X
                                                   >
                                         ))
                                       )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 a1, A2 const& a2, A3 const& a3) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a1, A0, typename std::iterator_traits<A1>::value_type);
      boost::simd::store(a0, a1, a2, a3);
    }
  };

  /// INTERNAL ONLY - Scatter SIMD store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::aligned_store_, tag::cpu_
                                       , (A0)(A1)(A2)(X)(Y)
                                       , (mpl::equal_to
                                            < boost::simd::meta::cardinal_of<A0>
                                            , boost::simd::meta::cardinal_of<A2>
                                            >
                                         )
                                       , ((simd_< unspecified_<A0>, X >))
                                         (iterator_< unspecified_<A1>  >)
                                         ((simd_< integer_<A2>, Y >))
                                       )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR_CVT(a1, A0, typename std::iterator_traits<A1>::value_type);
      boost::simd::store(a0, a1, a2);
    }
  };

  /// INTERNAL ONLY - Masked SIMD store for interlacing or logical
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (iterator_< unspecified_<A1> >)
                                      ((simd_< logical_<A2>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 a1, A2 const& a2) const
    {
      boost::simd::store(a0, a1, a2);
    }
  };

  /// INTERNAL ONLY - SIMD store for interlacing or logical
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_
                                    , tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_< unspecified_<A0>, X >))
                                      (iterator_< unspecified_<A1> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 a1) const
    {
      boost::simd::store(a0, a1);
    }
  };

  /// INTERNAL ONLY - SIMD Fusion sequence store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_, tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , ((simd_< fusion_sequence_<A0>, X >))
                                      (fusion_sequence_<A1>)
                                      (generic_< integer_<A2> >)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, A2 const& a2) const
    {
      static const int N = fusion::result_of::size<A1>::type::value;
      meta::iterate<N>( details::storer< boost::simd::
                                         tag::aligned_store_(A0, A1, A2)
                                       >(a0, a1, a2)
                      );
    }
  };
  /// INTERNAL ONLY - SIMD Fusion sequence store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_store_, tag::cpu_
                                    , (A0)(A1)(X)
                                    , ((simd_< fusion_sequence_<A0>, X >))
                                      (fusion_sequence_<A1>)
                                    )
  {
    typedef void result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1) const
    {
      static const int N = fusion::result_of::size<A1>::type::value;
      meta::iterate<N>( details::storer< boost::simd::
                                         tag::aligned_store_(A0, A1)
                                       >(a0, a1)
                      );
    }
  };
} } }

#endif

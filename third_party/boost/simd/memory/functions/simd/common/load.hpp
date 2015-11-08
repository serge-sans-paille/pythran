//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_LOAD_HPP_INCLUDED

#include <boost/simd/memory/functions/load.hpp>
#include <boost/simd/memory/functions/details/load.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

#include <boost/simd/operator/functions/if_else.hpp>
#include <boost/simd/constant/constants/zero.hpp>
#include <boost/simd/constant/constants/false.hpp>

#include <boost/simd/memory/functions/details/zero_or_false.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - SIMD mask load via Scalar emulation without offset, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A1>, X> >))
                                      ((simd_< logical_<A2>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef typename A1::type result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&, A2 const& a2) const
    {
      return load<result_type>(a0,a2,details::Zero_or_False<result_type>());
    }
  };

  /// INTERNAL ONLY - SIMD mask load via Scalar emulation without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A1>, X> >))
                                      ((simd_< logical_<A2>
                                             , X
                                             >
                                      ))
                                      ((simd_< unspecified_<A3>, X>))
                                    )
  {
    typedef typename A1::type result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&, A2 const& a2, A3 const& a3 ) const
    {
      return if_else(a2,load<result_type>(a0),a3);
    }
  };

  /// INTERNAL ONLY - SIMD load via Scalar emulation without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A2>, X> >))
                                    )
  {
    typedef typename A2::type result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A2 const&) const
    {
      result_type that;
      for(std::size_t i=0; i!=meta::cardinal_of<result_type>::value; ++i)
        that[i] = static_cast<stype>(a0[i]);
      return that;
    }
  };

  /// INTERNAL ONLY - SIMD mask load via Scalar emulation with scalar offset, zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A1>, X> >))
                                      (scalar_< integer_<A2> >)
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                    )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&, A2 a2, A3 const& a3) const
    {
      return load<result_type>(a0+a2,a3);
    }
  };

  /// INTERNAL ONLY - SIMD mask load via Scalar emulation with scalar offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)(A4)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A1>, X> >))
                                      (scalar_< integer_<A2> >)
                                      ((simd_< logical_<A3>
                                             , X
                                             >
                                      ))
                                      ((simd_< unspecified_<A4>, X>))
                                    )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&, A2 a2, A3 const& a3, A4 const& a4) const
    {
      return load<result_type>(a0+a2,a3,a4);
    }
  };

  /// INTERNAL ONLY - SIMD load via Scalar emulation with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (iterator_<unspecified_<A0> >)
                                      ((target_<simd_< unspecified_<A1>, X> >))
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef typename A1::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&, A2 a2) const
    {
      return load<result_type>(a0+a2);
    }
  };

  /// INTERNAL ONLY - Unaligned gather
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::load_
                                       , tag::cpu_
                                       , (A0)(A1)(A2)(X)(Y)
                                       , (mpl::equal_to
                                         < boost::simd::meta
                                           ::cardinal_of<typename A1::type>
                                         , boost::simd::meta
                                           ::cardinal_of<A2>
                                         >
                                         )
                                       , (iterator_< unspecified_<A0> >)
                                         ((target_<simd_<unspecified_<A1>, Y> >))
                                         ((simd_< integer_<A2>, X >))
                                       )
  {
    typedef typename A1::type                           result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, const A1&, const A2& a2) const
    {
      BOOST_ASSERT_MSG( meta::cardinal_of<result_type>::value == meta::cardinal_of<A2>::value
                      , "inconsistent cardinal in load gather"
                      );

      result_type that;
      for(std::size_t i=0; i!=meta::cardinal_of<result_type>::value; ++i)
      {
        stype value = static_cast<stype>(a0[a2[i]]);
#if defined(__INTEL_COMPILER) && defined(__MIC__)
        asm volatile(""::"m"(value));
#endif
        that[i] = value;
      }
      return that;
    }
  };

  /// INTERNAL ONLY - Masked unaligned gather zero
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::load_
                                       , tag::cpu_
                                       , (A0)(A1)(A2)(A3)(X)(Y)
                                       , (mpl::equal_to
                                         < boost::simd::meta
                                           ::cardinal_of<typename A1::type>
                                         , boost::simd::meta
                                           ::cardinal_of<A2>
                                         >
                                         )
                                       , (iterator_< unspecified_<A0> >)
                                         ((target_<simd_<unspecified_<A1>, Y> >))
                                         ((simd_< integer_<A2>, X >))
                                         ((simd_< logical_<A3>
                                                , Y
                                                >
                                         ))
                                       )
  {
    typedef typename A1::type                           result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, const A1&, const A2& a2, const A3& a3 ) const
    {
      return load<result_type>(a0,a2,a3,details::Zero_or_False<result_type>());
    }
  };

  /// INTERNAL ONLY - Masked unaligned gather
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF ( boost::simd::tag::load_
                                       , tag::cpu_
                                       , (A0)(A1)(A2)(A3)(A4)(X)(Y)
                                       , (mpl::equal_to
                                         < boost::simd::meta
                                           ::cardinal_of<typename A1::type>
                                         , boost::simd::meta
                                           ::cardinal_of<A2>
                                         >
                                         )
                                       , (iterator_< unspecified_<A0> >)
                                         ((target_<simd_<unspecified_<A1>, Y> >))
                                         ((simd_< integer_<A2>, X >))
                                         ((simd_< logical_<A3>
                                                , Y
                                                >
                                         ))
                                         ((simd_< unspecified_<A4>, Y>))
                                       )
  {
    typedef typename A1::type                           result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, const A1&, const A2& a2, const A3& a3, const A4& a4 ) const
    {
      BOOST_ASSERT_MSG( meta::cardinal_of<result_type>::value == meta::cardinal_of<A2>::value
                     && meta::cardinal_of<result_type>::value == meta::cardinal_of<A3>::value
                      , "inconsistent cardinal in load masked gather"
                      );

      result_type that;
      for(std::size_t i=0; i!=meta::cardinal_of<result_type>::value; ++i)
      {
        stype value = static_cast<stype>(a0[a2[i]]);
#if defined(__INTEL_COMPILER) && defined(__MIC__)
        asm volatile(""::"m"(value));
#endif
        that[i] = if_else(a3[i],value,static_cast<stype>(a4[i]));
      }
      return that;
    }
  };

  /// INTERNAL ONLY - SIMD unaligned load for Fusion Sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (fusion_sequence_<A0>)
                                      ((target_ < simd_ < fusion_sequence_<A1>
                                                        , X
                                                        >
                                                >
                                      ))
                                      (generic_< integer_<A2> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& a0, const A1&, const A2& a2) const
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      result_type that;
      meta::iterate<N>( details::loader< boost::simd::
                                         tag::load_(A0, result_type, A2)
                                       >(a0, that, a2)
                      );
      return that;
    }
  };

  /// INTERNAL ONLY - SIMD unaligned load for Fusion Sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)(X)
                                    , (fusion_sequence_<A0>)
                                      ((target_ < simd_ < fusion_sequence_<A2>
                                                        , X
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(const A0& a0, const A2&) const
    {
      static const int N = fusion::result_of::size<A0>::type::value;
      result_type that;
      meta::iterate<N>( details::loader< boost::simd::
                                         tag::load_(A0, result_type)
                                       >(a0, that)
                      );
      return that;
    }
  };
} } }

#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/false.hpp>

#endif

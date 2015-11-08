//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_PACK_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/include/functions/aligned_load.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/simd/pack/forward.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/mpl.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Load pack with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (iterator_< unspecified_<A0> >)
                                      ((target_ < ast_< A1
                                                      , boost::simd::domain
                                                      >
                                                >
                                      ))
                                      (scalar_< integer_<A2> >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&, A2 const& a2) const
    {
      return boost::simd::aligned_load<typename result_type::data_type>(a0, a2);
    }
  };

  /// INTERNAL ONLY - Load pack with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(X)
                                    , (iterator_< unspecified_<A0> >)
                                      ((target_ < ast_< A1
                                                      , boost::simd::domain
                                                      >
                                                >
                                      ))
                                      ((simd_< integer_<A2>, X >))
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A1 const&, A2 const& a2) const
    {
      return boost::simd::aligned_load<typename result_type::data_type>(a0, a2);
    }
  };

  /// INTERNAL ONLY - Load pack without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A2)
                                    , (iterator_< unspecified_<A0> >)
                                      ((target_ < ast_< A2
                                                      , boost::simd::domain
                                                      >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A2 const&) const
    {
      return boost::simd::aligned_load<typename result_type::data_type>(a0);
    }
  };

  /// INTERNAL ONLY - Load misaligned pack with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)(A3)
                                    , (iterator_< unspecified_<A0> >)
                                      ((target_< ast_<A1, boost::simd::domain> >))
                                      (scalar_< integer_<A2> >)
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 const&, A2 const& a2, A3 const&) const
    {
      return boost::simd::aligned_load< typename result_type::data_type
                              , A3::value
                              >(a0,a2);
    }
  };

  /// INTERNAL ONLY - Load misaligned pack without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_ , tag::cpu_
                                    , (A0)(A2)(A3)
                                    , (iterator_< unspecified_<A0> >)
                                      ((target_< ast_<A2, boost::simd::domain> >))
                                      (mpl_integral_< scalar_< integer_<A3> > >)
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A2 const&, A3 const&) const
    {
      return boost::simd::aligned_load< typename result_type::data_type
                              , A3::value
                              >(a0);
    }
  };
} } }

#endif

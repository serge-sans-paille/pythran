//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_ALL_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_ALL_REDUCE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT

#include <boost/simd/swar/functions/all_reduce.hpp>
#include <boost/simd/swar/functions/details/butterfly.hpp>
#include <boost/simd/sdk/simd/category.hpp>

// Those overload are there so when we use SSSE3, we use the faster
// shuffle_epi8 instead of the SSE2 web of shuffles required for those
// types.

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::simd_
                                    , (Tag)(A0)(X)
                                    , ((simd_< type16_<A0>, X >))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      typedef typename boost::simd::meta::cardinal_of<result_type>::type card;
      details::butterfly<card::value/2,result_type> callee;
      return callee(base(),a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::simd_
                                    , (Tag)(A0)(X)
                                    , ((simd_< type8_<A0>, X >))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      typedef typename boost::simd::meta::cardinal_of<result_type>::type card;
      details::butterfly<card::value/2,result_type> callee;
      return callee(base(),a0);
    }
  };
} } }

#endif
#endif

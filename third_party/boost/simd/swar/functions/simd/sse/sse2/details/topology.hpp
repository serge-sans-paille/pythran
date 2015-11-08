//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DETAILS_TOPOLOGY_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DETAILS_TOPOLOGY_HPP_INCLUDED

#include <boost/simd/swar/functions/details/permuted.hpp>
#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Make a MM_SHUFFLE from a Permutation and Cardinal
  //============================================================================
  template<typename P, std::size_t Cardinal> struct  shuffle_mask;

  template<typename P>
  struct  shuffle_mask<P,2>
        : boost::mpl::int_
          < _MM_SHUFFLE2( (details::permuted<details::fix_zero<P>,1,2>::value)
                        , (details::permuted<details::fix_zero<P>,0,2>::value)
                        )
          >
  {};

  template<typename P>
  struct  shuffle_mask<P,4>
        : boost::mpl::int_
          < _MM_SHUFFLE ( (details::permuted<details::fix_zero<P>,3,4>::value)
                        , (details::permuted<details::fix_zero<P>,2,4>::value)
                        , (details::permuted<details::fix_zero<P>,1,4>::value)
                        , (details::permuted<details::fix_zero<P>,0,4>::value)
                        )
          >
  {};

  //============================================================================
  // Markup for SSE2 topology
  // direct_    means the pattern is of the shape { a0 | a1 }
  // indirect_  means the pattern is of the shape { a1 | a0 }
  // mixed_     means the pattern is random
  //============================================================================
  typedef boost::mpl::int_<-1>  indirect_;
  typedef boost::mpl::int_<0>   mixed_;
  typedef boost::mpl::int_<1>   direct_;

  //============================================================================
  // Check if a permutation follows SSE2 shuffle restriction in a way or another
  //============================================================================
  template<typename Permutation, std::size_t Cardinal>
  struct sse2_topology
  {
    typedef indirect_ type;
  };

  //============================================================================
  // Cardinal 2 is either direct or indirect, no room for mixed
  //============================================================================
  template<typename Permutation>
  struct sse2_topology<Permutation,2>
  {
    static const int p0 = permuted<Permutation,0,2>::value;
    static const int p1 = permuted<Permutation,1,2>::value;

    typedef typename mpl::if_c< (p0 <= 1) && (p1 >= 2)
                              , direct_
                              , indirect_
                              >::type type;
  };

  //============================================================================
  // Cardinal 4 can be anything
  //============================================================================
  template<typename Permutation>
  struct sse2_topology<Permutation,4>
  {
    static const int p0 = permuted<Permutation,0,4>::value;
    static const int p1 = permuted<Permutation,1,4>::value;
    static const int p2 = permuted<Permutation,2,4>::value;
    static const int p3 = permuted<Permutation,3,4>::value;

    static const bool is_direct =   (p0 < 4 ) &&  (p1 < 4 )
                                &&  (p2 >= 4) &&  (p3 >= 4);

    static const bool is_indirect =   (p2 < 4 ) &&  (p3 < 4 )
                                  &&  (p0 >= 4) &&  (p1 >= 4);

    typedef typename mpl::eval_if_c < is_direct
                                    , direct_
                                    , mpl::eval_if_c< is_indirect
                                                    , indirect_
                                                    , mixed_
                                                    >
                                    >::type type;
  };
} } }

#endif

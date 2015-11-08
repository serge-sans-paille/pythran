//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_DETAILS_TOPOLOGY_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_DETAILS_TOPOLOGY_HPP_INCLUDED

#include <boost/simd/swar/functions/details/permuted.hpp>
#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/simd/swar/functions/simd/sse/sse2/details/topology.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // Make a AVX MM_SHUFFLE from a Permutation and Cardinal
  //============================================================================
  template<typename P, std::size_t Cardinal> struct avx_mask;

  template<typename P>
  struct  avx_mask<P,4>
        : boost::mpl::int_
          < ( ((details::permuted<details::fix_zero<P>,3,4>::value)&1)<<3
            | ((details::permuted<details::fix_zero<P>,2,4>::value)&1)<<2
            | ((details::permuted<details::fix_zero<P>,1,4>::value)&1)<<1
            | ((details::permuted<details::fix_zero<P>,0,4>::value)&1)
            )
          >
  {};

  template<typename P>
  struct  avx_mask<P,8>
        : boost::mpl::int_
          < ( ((details::permuted<details::fix_zero<P>,3,8>::value)&3)<<6
            | ((details::permuted<details::fix_zero<P>,2,8>::value)&3)<<4
            | ((details::permuted<details::fix_zero<P>,1,8>::value)&3)<<2
            | ((details::permuted<details::fix_zero<P>,0,8>::value)&3)
            )
          >
  {};

  template<typename P, std::size_t Cardinal> struct avx_blend_mask;

  template<typename P>
  struct  avx_blend_mask<P,4>
        : boost::mpl::int_
          < ( (details::permuted<details::fix_zero<P>,3,4>::value==7)<<3
            | (details::permuted<details::fix_zero<P>,2,4>::value==6)<<2
            | (details::permuted<details::fix_zero<P>,1,4>::value==5)<<1
            | (details::permuted<details::fix_zero<P>,0,4>::value==4)
            )
          >
  {};

  //============================================================================
  // Markup for AVX topology
  //============================================================================
  typedef boost::mpl::int_<2>   swap_;
  typedef boost::mpl::int_<4>   dupe_;
  typedef boost::mpl::int_<8>   r_zero_;
  typedef boost::mpl::int_<16>  l_zero_;
  typedef boost::mpl::int_<32>  blend_;

  //============================================================================
  // Check if a permutation follows AVX shuffle restriction in a way or another
  //============================================================================
  template<typename Permutation, std::size_t Cardinal>
  struct avx_topology;

  //============================================================================
  // Cardinal 2 is either direct or indirect, no room for mixed
  //============================================================================
  template<typename Permutation>
  struct avx_topology<Permutation,4>
  {
    static const int p0 = permuted<Permutation,0,4>::value;
    static const int p1 = permuted<Permutation,1,4>::value;
    static const int p2 = permuted<Permutation,2,4>::value;
    static const int p3 = permuted<Permutation,3,4>::value;

    // Check for shuffle_pd(a0,a1) calls
    static const bool direct_shf  =   (p0==0 || p0==1)  &&  (p1==4 || p1==5)
                                  &&  (p2==2 || p2==3)  &&  (p3==6 || p3==7);

    // Check for shuffle_pd(a0,zero) calls
    static const bool r_zero_shf  =   (p0==0 || p0==1)  &&  (p1==-1)
                                  &&  (p2==2 || p2==3)  &&  (p3==-1);

    // Check for shuffle_pd(zero,a0) calls
    static const bool l_zero_shf  =   (p0 == -1)  &&  (p1==0 || p1==1)
                                  &&  (p2 == -1)  &&  (p3==2 || p3==3);

    // Check for shuffle_pd(a0,a0) calls
    static const bool dupe_shf  =   (p0==0 || p0==1)  &&  (p1==0 || p1==1)
                                &&  (p2==2 || p2==3)  &&  (p3==2 || p3==3);

    // Check for shuffle_pd(a1,a0) calls
    static const bool swap_shf  =   (p0==4 || p0==5)  &&  (p1==0 || p1==1)
                                &&  (p2==6 || p2==7)  &&  (p3==2 || p3==3);

    // Check for _mm256_blend_pd(a1,a0) calls
    static const bool blend_shf  =   !(direct_shf | swap_shf | dupe_shf)
                                && ((p0==0 || p0==4)  &&  (p1==1 || p1==5)
                                &&  (p2==2 || p2==6)  &&  (p3==3 || p3==7));
    // Compute topology mask
    typedef boost::mpl::int_< int(direct_shf)
                            + int(swap_shf  )*2 + int(dupe_shf  )*4
                            + int(r_zero_shf)*8 + int(l_zero_shf)*16
                            + int(blend_shf)*32
                            > type;
  };

  template<typename Permutation>
  struct avx_topology<Permutation,8>
  {
    static const int p0 = permuted<Permutation,0,8>::value;
    static const int p1 = permuted<Permutation,1,8>::value;
    static const int p2 = permuted<Permutation,2,8>::value;
    static const int p3 = permuted<Permutation,3,8>::value;
    static const int p4 = permuted<Permutation,4,8>::value;
    static const int p5 = permuted<Permutation,5,8>::value;
    static const int p6 = permuted<Permutation,6,8>::value;
    static const int p7 = permuted<Permutation,7,8>::value;

    // Check for shuffle_ps(a0,a1) calls (~65536 calls)
    static const bool direct_shf  =   (p0 < 4  && p1 < 4  && p0 >=0 && p1 >= 0)
                                  &&  (p2 < 12 && p3 < 12 && p2 >=8 && p3 >= 8)
                                  &&  (p4 == p0+4 && p5 == p1+4)
                                  &&  (p6 == p2+4 && p7 == p3+4);

    // Check for shuffle_ps(a0,a0) calls (~65536 calls)
    static const bool dupe_shf  =   (p0 < 4 && p1 < 4 && p0 >=0 && p1 >= 0)
                                &&  (p2 < 4 && p3 < 4 && p2 >=0 && p3 >= 0)
                                &&  (p4 == p0+4 && p5 == p1+4)
                                &&  (p6 == p2+4 && p7 == p3+4);

    // Check for shuffle_pd(a0,zero) calls
    static const bool r_zero_shf  =   (p0  <  4 && p1  <  4 && p0 >=0 && p1 >= 0)
                                  &&  (p2 == -1 && p3 == -1)
                                  &&  (p4 == p0+4 && p5 == p1+4)
                                  &&  (p6 == -1 && p7 == -1);

    // Check for shuffle_ps(zero,a0) calls (~65536 calls)
    static const bool l_zero_shf  =   (p0 == -1 && p1 == -1)
                                  &&  (p2 < 4 && p3 < 4 && p2 >=0 && p3 >= 0)
                                  &&  (p4 == -1 && p5 == -1)
                                  &&  (p6 == p2+4 && p7 == p3+4);

    // Check for shuffle_ps(a1,a0) calls (~65536 calls)
    static const bool swap_shf  =   (p0 < 12 && p1 < 12 && p0 >=8 && p1 >= 8)
                                &&  (p2 < 4  && p3 < 4  && p2 >=0 && p3 >= 0)
                                &&  (p4 == p0+4 && p5 == p1+4)
                                &&  (p6 == p2+4 && p7 == p3+4);
    // Compute topology mask
    typedef boost::mpl::int_< int(direct_shf)
                            + int(swap_shf  )*2 + int(dupe_shf  )*4
                            + int(r_zero_shf)*8 + int(l_zero_shf)*16
                            > type;
  };

} } }

#endif

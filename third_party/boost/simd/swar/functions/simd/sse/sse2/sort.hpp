//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SORT_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_SORT_HPP_INCLUDED

#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/swar/functions/sort.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/functions/simd/minimum.hpp>
#include <boost/simd/include/functions/simd/maximum.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/swar/functions/shuffle.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sort_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < type32_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // half-permute
      A0 p0 = shuffle<2,3,0,1>(a0);
      A0 mn = min(a0,p0);
      A0 mx = max(a0,p0);

      // cross vector concatenation and reversal
      A0 minmax = shuffle<0,1,6,7>(mn,mx);
      A0 maxmin = shuffle<1,0,7,6>(mn,mx);

      mn = min(minmax,maxmin);
      mx = max(minmax,maxmin);

      // rearrange partial max/min while keeping min and max in place
         p0 = shuffle<0,2,5,7>(mn,mx);
      A0 p1 = shuffle<0,2,1,3>(p0);

      // Bring sorted min/max in the proper place
      return shuffle<0,1,6,7>(min(p1,p0),max(p1,p0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::sort_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < type64_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      // Better latency
      A0 p0 = shuffle<1,0>(a0);
      return shuffle<0,2>(min(a0,p0),max(a0,p0));
    }
  };
} } }

#endif
#endif

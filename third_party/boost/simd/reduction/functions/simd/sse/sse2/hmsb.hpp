//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_HMSB_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_SSE2_HMSB_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/reduction/functions/hmsb.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < type8_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return _mm_movemask_epi8(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < type32_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename dispatch::meta::as_floating<A0>::type type;
      return _mm_movemask_ps(bitwise_cast<type>(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_ < type64_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                      )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename dispatch::meta::as_floating<A0>::type type;
      return _mm_movemask_pd(bitwise_cast<type>(a0));
    }
  };

} } }

#endif
#endif

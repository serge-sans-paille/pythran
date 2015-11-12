//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_SSSE3_HMSB_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_SSSE3_HMSB_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT

#include <boost/simd/reduction/functions/hmsb.hpp>
#include <boost/dispatch/attributes.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_
                                    , boost::simd::tag::ssse3_
                                    , (A0)
                                    , ((simd_ < type16_<A0>
                                              , boost::simd::tag::sse_
                                              >
                                      ))
                                    )
  {
    typedef std::size_t result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename A0::template rebind<char>::type s8type;

      __m128i mask =  _mm_setr_epi8 ( 0x01,0x03,0x05,0x07,0x09,0x0B,0x0D,0x0F
                                    , -128,-128,-128,-128,-128,-128,-128,-128
                                    );

      return _mm_movemask_epi8(_mm_shuffle_epi8(bitwise_cast<s8type>(a0),mask));
    }
  };

} } }

#endif
#endif

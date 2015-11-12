//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_LOOKUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT

#include <boost/simd/swar/functions/lookup.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::lookup_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(A1)
                                    , ((simd_<type8_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<ints8_<A1>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return _mm_shuffle_epi8(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::lookup_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(A1)
                                    , ((simd_<type16_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<ints16_<A1>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename A0::template rebind<char>::type  type8;

      const type8 inc = make<type8>(0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1);
      const type8 dup = make<type8>(0,0,2,2,4,4,6,6,8,8,10,10,12,12,14,14);

      const type8 i1 = _mm_shuffle_epi8(shl(a1, 1), dup);

      return _mm_shuffle_epi8(simd::bitwise_cast<type8>(a0),i1+inc);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::lookup_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(A1)
                                    , ((simd_<type32_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<ints32_<A1>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename A0::template rebind<char>::type  type8;

      const type8 inc = make<type8> ( 0, 1, 2, 3, 0, 1, 2, 3
                                    , 0, 1, 2, 3, 0, 1, 2, 3
                                    );

      const type8 dup = make<type8> ( 0, 0, 0, 0, 4, 4, 4, 4
                                    , 8, 8, 8, 8, 12, 12, 12, 12
                                    );

      type8 i1 = _mm_shuffle_epi8(shl(a1, 2), dup);
      type8  r = _mm_shuffle_epi8(simd::bitwise_cast<type8>(a0), i1+inc );

      return simd::bitwise_cast<A0>(r);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::lookup_
                                    , boost::simd::tag::ssse3_
                                    , (A0)(A1)
                                    , ((simd_<type64_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<ints64_<A1>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename A0::template rebind<char>::type  type8;

      const type8 inc = make<type8> ( 0, 1, 2, 3, 4, 5, 6, 7
                                    , 0, 1, 2, 3, 4, 5, 6, 7
                                    );

      const type8 dup = make<type8> ( 0, 0, 0, 0, 0, 0, 0, 0
                                    , 8, 8, 8, 8, 8, 8, 8, 8
                                    );

      const type8 i1 = _mm_shuffle_epi8(shl(a1, 3), dup);
      const type8 r  = _mm_shuffle_epi8(simd::bitwise_cast<type8>(a0), i1+inc);

      return simd::bitwise_cast<A0>(r);
    }
  };
} } }
#endif
#endif

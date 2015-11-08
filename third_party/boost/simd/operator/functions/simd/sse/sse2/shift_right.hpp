//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_SHIFT_RIGHT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/operator/functions/shift_right.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_ornot.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/is_ltz.hpp>
#include <boost/simd/include/functions/simd/if_else_allbits.hpp>
#include <boost/simd/include/functions/simd/group.hpp>
#include <boost/simd/include/functions/simd/split.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/include/constants/allbits.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_right_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<int8_<A0>,boost::simd::tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0                                              result_type;
    typedef typename meta::make_dependent<int16_t,A0>::type sub_t;
    typedef native<sub_t, boost::simd::tag::sse_>           gen_t;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right sse2 int8: a shift is out of range");
      gen_t a0h, a0l;
      split(a0, a0l, a0h);
      return group(shift_right(a0l, a1), shift_right(a0h, a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_right_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right sse2 int16: a shift is out of range");
      return _mm_srai_epi16(a0, int(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_right_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right sse2 int32: a shift is out of range");
      return _mm_srai_epi32(a0, int(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_right_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right sse2 int64: a shift is out of range");
      A0 that = _mm_srli_epi64(a0, int(a1));
      A0 mask = _mm_srli_epi64(Allbits<A0>(), int(a1));
      return b_ornot(that, if_else_allbits(is_ltz(a0), mask));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_right_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    typedef typename meta::make_dependent<int32_t,A0>::type int_t;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right sse2 uint8: a shift is out of range");
      typedef native<int_t, boost::simd::tag::sse_> gen_type;
      result_type const Mask1 = bitwise_cast<result_type>(boost::simd::integral_constant<gen_type, int_t(0x00ff00ff)>());
      result_type const Mask2 = bitwise_cast<result_type>(boost::simd::integral_constant<gen_type, int_t(0xff00ff00)>());

      result_type tmp  = b_and(a0, Mask1);
      result_type tmp1 = _mm_srli_epi16(tmp, int(a1));
      tmp1 = b_and(tmp1, Mask1);
      tmp = b_and(a0, Mask2);
      result_type tmp3 = _mm_srli_epi16(tmp, int(a1));
      return tmp1 | b_and(tmp3, Mask2);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_right_, boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right sse2 uint16: a shift is out of range");
      return _mm_srli_epi16(a0, int(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_right_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right sse2 uint32: a shift is out of range");
      return _mm_srli_epi32(a0, int(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::shift_right_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)
                                    , ((simd_<uint64_<A0>,boost::simd::tag::sse_>))
                                      (scalar_< integer_<A1> >)
                                    )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right sse2 uint64: a shift is out of range");
      return _mm_srli_epi64(a0, int(a1));
    }
  };
} } }

#endif
#endif

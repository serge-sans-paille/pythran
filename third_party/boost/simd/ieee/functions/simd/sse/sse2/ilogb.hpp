//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_SSE_SSE2_ILOGB_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_SSE_SSE2_ILOGB_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/ieee/functions/ilogb.hpp>
#include <boost/simd/include/functions/simd/tofloat.hpp>
#include <boost/simd/include/functions/simd/exponent.hpp>
#include <boost/simd/include/functions/simd/seladd.hpp>
#include <boost/simd/include/functions/simd/is_gtz.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/is_eqz.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/constants/one.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#define MKN(N) simd::bitwise_cast<vtype##N>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::ilogb_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<int_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type  result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_integer<A0,unsigned>::type vtype;
      static const A0 z = Zero<A0>();
      vtype tmp = ilogb(simd::bitwise_cast<vtype>(a0));
      return seladd(is_gtz(a0), z, simd::bitwise_cast<A0>(tmp));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::ilogb_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<uint8_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type  result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef A0 vtype8;
      static const vtype8& o = One<vtype8>();
      static const vtype8 mask =  boost::simd::integral_constant<vtype8, 0x7f>();
      vtype8 n = a0;
      vtype8 i = o;
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o);
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o);
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o);
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o);
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o);
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o);
      n = b_and(MKN(8)(_mm_srli_epi16(n, 1)), mask);
      i = seladd(is_nez(n), i, o);
      return i-o;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::ilogb_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<uint32_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type  result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename A0::extension_type cat;
      typedef A0 vtype32;
      typedef simd::native<boost::uint8_t, cat>  vtype8;
      static const vtype8& z = Zero<vtype8>();
      static const vtype8& o = One<vtype8>();
      static const vtype32 mask = boost::simd::integral_constant<vtype32, 0x7f7f7f7f>();
      vtype8 i = if_else(is_eqz(MKN(8)(a0)), z, o);
      vtype8 n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(a0, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(32)(_mm_srli_epi16(MKN(32)(n), 1)), mask));
      i = seladd(is_nez(n), i, o);
      static const vtype32 mask1 = boost::simd::integral_constant<vtype32,0x000000ff>();
      static const vtype32 mask2 = boost::simd::integral_constant<vtype32,0x0000ff00>();
      static const vtype32 mask3 = boost::simd::integral_constant<vtype32,0x00ff0000>();
      static const vtype32 mask4 = boost::simd::integral_constant<vtype32,0xff000000>();
      static const vtype32 huit  = boost::simd::integral_constant<vtype32,8>();
      static const vtype32 seize = boost::simd::integral_constant<vtype32,16u>();
      static const vtype32 v4    = boost::simd::integral_constant<vtype32,24u>();
      vtype32 yy = b_and(MKN(32)(i), mask4);
      vtype32 zz = b_and(MKN(32)(i), mask3);
      vtype32 tt = b_and(MKN(32)(i), mask2);
      vtype32 uu = b_and(MKN(32)(i), mask1);
      vtype32 xx = if_else(is_nez(yy), MKN(32)(_mm_srli_epi32(yy,24))+v4,
                 if_else(is_nez(zz), MKN(32)(_mm_srli_epi32(zz,16))+seize,
                   if_else(is_nez(tt), MKN(32)(_mm_srli_epi32(tt,8))+huit,
                       uu)));
      return MKN(32)(is_nez(MKN(8)(xx))&(MKN(8)(xx)-o));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::ilogb_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<uint64_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type  result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename A0::extension_type cat;
      typedef simd::native<boost::uint64_t, cat> vtype64;
      return simd::bitwise_cast<vtype64>(exponent(tofloat(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::ilogb_, boost::simd::tag::sse2_,
                        (A0),
                        ((simd_<uint16_<A0>,boost::simd::tag::sse_>))
                       )
  {
    typedef typename dispatch::meta::as_integer<A0>::type  result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef A0 vtype16;
      typedef typename A0::extension_type cat;
      typedef simd::native<boost::uint8_t, cat>  vtype8;
      static const vtype8& z = Zero<vtype8>();
      static const vtype8& o = One<vtype8>();
      static const vtype16 mask =  boost::simd::integral_constant<vtype16, 0x7f7f > ();
      vtype8 i = if_else(is_eqz(MKN(8)(a0)), z, o);
      vtype8 n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(a0, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      n = MKN(8)(b_and(MKN(16)(_mm_srli_epi16(n, 1)), mask));
      i = seladd(is_nez(n), i, o);
      static const vtype16 mask1 = boost::simd::integral_constant<vtype16, 0x00ff>();
      static const vtype16 mask2 = boost::simd::integral_constant<vtype16, 0xff00>();
      static const vtype16 huit  = boost::simd::integral_constant<vtype16, 8u>();
      vtype16 yy = b_and(MKN(16)(i), mask2);
      vtype16 zz = b_and(MKN(16)(i), mask1);
      vtype16 xx = if_else(is_nez(yy), MKN(16)(_mm_srli_epi16(yy, 8))+huit, zz);
      return MKN(16)(is_nez(MKN(8)(xx))&(MKN(8)(xx)-o));
    }
  };
} } }

#undef MKN

#endif
#endif

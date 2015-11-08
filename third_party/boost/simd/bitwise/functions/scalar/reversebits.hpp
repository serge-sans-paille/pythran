//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_REVERSEBITS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SCALAR_REVERSEBITS_HPP_INCLUDED

#include <boost/simd/bitwise/functions/reversebits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reversebits_, tag::cpu_
                            , (A0)
                            , (scalar_< ints8_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return uint8_t(
        ((uint8_t(a0) * 0x0802LU & 0x22110LU) | (uint8_t(a0) * 0x8020LU & 0x88440LU)) * 0x10101LU >> 16
      );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reversebits_, tag::cpu_
                            , (A0)
                            , (scalar_< ints64_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      union { A0 a; boost::simd::uint32_t b[2]; } z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return z.a;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reversebits_, tag::cpu_
                            , (A0)
                            , (scalar_< ints16_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      union { A0 a; boost::simd::uint8_t b[2]; } z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return  z.a;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reversebits_, tag::cpu_
                            , (A0)
                            , (scalar_< ints32_<A0> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      union { A0 a; boost::simd::uint16_t b[2]; } z = {a0};
      z.b[0] = reversebits(z.b[0]);
      z.b[1] = reversebits(z.b[1]);
      std::swap(z.b[0], z.b[1]);
      return z.a;
    }
  };
} } }

#endif

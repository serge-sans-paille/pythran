//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_REVERSEBITS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SIMD_COMMON_REVERSEBITS_HPP_INCLUDED

#include <boost/simd/bitwise/functions/reversebits.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/include/functions/simd/shr.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reversebits_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int8_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type utype;
      utype v = bitwise_cast<utype>(a0);
      const utype m1  = integral_constant<utype,0x55>(); //binary: 0101...
      const utype m2  = integral_constant<utype,0x33>(); //binary: 00110011..
      const utype m4  = integral_constant<utype,0x0f>(); //binary:  4 zeros,  4 ones ...
      // swap odd and even bits
      v = (shri(v, 1) & m1) | shli((v & m1), 1);
      // swap consecutive pairs
      v = (shri(v, 2) & m2) | shli((v & m2), 2);
      // swap nibbles ...
      v = (shri(v, 4) & m4) | shli((v & m4), 4);
      return bitwise_cast<A0>(v);
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reversebits_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int64_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type utype;
      utype v = bitwise_cast<utype>(a0);
      const result_type m1  = integral_constant<result_type,0x5555555555555555ull>(); //binary: 0101...
      const result_type m2  = integral_constant<result_type,0x3333333333333333ull>(); //binary: 00110011..
      const result_type m4  = integral_constant<result_type,0x0f0f0f0f0f0f0f0full>(); //binary:  4 zeros,  4 ones ...
      const result_type m8  = integral_constant<result_type,0x00ff00ff00ff00ffull>(); //binary:  8 zeros,  8 ones ...
      const result_type m16 = integral_constant<result_type,0x0000ffff0000ffffull>(); //binary:  16 zeros,  16 ones ...
      const result_type m32 = integral_constant<result_type,0x00000000ffffffffull>(); //binary:  32 zeros,  32 ones ...
      // swap odd and even bits
      v = (shri(v, 1) & m1) | shli((v & m1), 1);
      // swap consecutive pairs
      v = (shri(v, 2) & m2) | shli((v & m2), 2);
      // swap nibbles ...
      v = (shri(v, 4) & m4) | shli((v & m4), 4);
      // swap bytes ...
      v = (shri(v, 8) & m8) | shli((v & m8), 8);
      // swap shorts ...
      v = (shri(v, 16) & m16) | shli((v & m16), 16);
      // swap ints ...
      v = (shri(v, 32) & m32) | shli((v & m32), 32);
      return bitwise_cast<A0>(v);
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reversebits_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int16_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      using boost::simd::integral_constant;
      using boost::simd::bitwise_cast;

      typedef typename dispatch::meta::as_integer<A0, unsigned>::type utype;
      utype v = bitwise_cast<utype>(a0);
      const result_type m1  = integral_constant<result_type,0x5555>(); //binary: 0101...
      const result_type m2  = integral_constant<result_type,0x3333>(); //binary: 00110011..
      const result_type m4  = integral_constant<result_type,0x0f0f>(); //binary:  4 zeros,  4 ones ...
      const result_type m8  = integral_constant<result_type,0x00ff>(); //binary:  8 zeros,  8 ones ...
      // swap odd and even bits
      v = (shri(v, 1) & m1) | shli((v & m1), 1);
      // swap consecutive pairs
      v = (shri(v, 2) & m2) | shli((v & m2), 2);
      // swap nibbles ...
      v = (shri(v, 4) & m4) | shli((v & m4), 4);
      // swap bytes ...
      v = (shri(v, 8) & m8) | shli((v & m8), 8);
      return bitwise_cast<A0>(v);
      }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::reversebits_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<int32_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::as_integer<A0, unsigned>::type utype;
      utype v = bitwise_cast<utype>(a0);
      const result_type m1  = integral_constant<result_type,0x55555555>(); //binary: 0101...
      const result_type m2  = integral_constant<result_type,0x33333333>(); //binary: 00110011..
      const result_type m4  = integral_constant<result_type,0x0f0f0f0f>(); //binary:  4 zeros,  4 ones ...
      const result_type m8  = integral_constant<result_type,0x00ff00ff>(); //binary:  8 zeros,  8 ones ...
      const result_type m16 = integral_constant<result_type,0x0000ffff>(); //binary:  16 zeros,  16 ones ...
      // swap odd and even bits
      v = (shri(v, 1) & m1) | shli((v & m1), 1);
      // swap consecutive pairs
      v = (shri(v, 2) & m2) | shli((v & m2), 2);
      // swap nibbles ...
      v = (shri(v, 4) & m4) | shli((v & m4), 4);
      // swap bytes ...
      v = (shri(v, 8) & m8) | shli((v & m8), 8);
      // swap shorts ...
      v = (shri(v, 16) & m16) | shli((v & m16), 16);
      return bitwise_cast<A0>(v);
      }
  };
} } }

#endif

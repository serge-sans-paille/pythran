//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REVERSEBITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REVERSEBITS_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(reversebits_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints8_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        using utype = bd::as_integer_t<A0, unsigned>;
        utype v = bitwise_cast<utype>(a0);
        const utype m1  = utype(0x55); //binary: 0101...
        const utype m2  = utype(0x33); //binary: 00110011..
        const utype m4  = utype(0x0f); //binary:  4 zeros,  4 ones ...
        // swap odd and even bits
        v = bitwise_or(bitwise_and(shr(v, 1), m1), shift_left(bitwise_and(v, m1), 1));
        // swap consecutive pairs
        v = bitwise_or(bitwise_and(shr(v, 2), m2), shift_left(bitwise_and(v, m2), 2));
        // swap nibbles ...
        v = bitwise_or(bitwise_and(shr(v, 4), m4), shift_left(bitwise_and(v, m4), 4));
        return bitwise_cast<A0>(v);
        }
   };

   BOOST_DISPATCH_OVERLOAD_IF(reversebits_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints64_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        using utype = bd::as_integer_t<A0, unsigned>;
        utype v = bitwise_cast<utype>(a0);
        const utype m1  = utype(0x5555555555555555ull); //binary: 0101...
        const utype m2  = utype(0x3333333333333333ull); //binary: 00110011..
        const utype m4  = utype(0x0f0f0f0f0f0f0f0full); //binary:  4 zeros,  4 ones ...
        const utype m8  = utype(0x00ff00ff00ff00ffull); //binary:  8 zeros,  8 ones ...
        const utype m16 = utype(0x0000ffff0000ffffull); //binary:  16 zeros,  16 ones ...
        const utype m32 = utype(0x00000000ffffffffull); //binary:  32 zeros,  32 ones ...
        // swap odd and even bits
        v = bitwise_or(bitwise_and(shr(v, 1), m1), shift_left(bitwise_and(v, m1), 1));
        // swap consecutive pairs
        v = bitwise_or(bitwise_and(shr(v, 2), m2), shift_left(bitwise_and(v, m2), 2));
        // swap nibbles ...
        v = bitwise_or(bitwise_and(shr(v, 4), m4), shift_left(bitwise_and(v, m4), 4));
        // swap bytes ...
        v = bitwise_or(bitwise_and(shr(v, 8), m8), shift_left(bitwise_and(v, m8), 8));
        // swap shorts ...
        v = bitwise_or(bitwise_and(shr(v, 16), m16), shift_left(bitwise_and(v, m16), 16));
        // swap ints ...
        v = bitwise_or(bitwise_and(shr(v, 32), m32), shift_left(bitwise_and(v, m32), 32));
        return bitwise_cast<A0>(v);
        }
   };

   BOOST_DISPATCH_OVERLOAD_IF(reversebits_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints16_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        using utype = bd::as_integer_t<A0, unsigned>;
        utype v = bitwise_cast<utype>(a0);
        const utype m1  = utype(0x5555); //binary: 0101...
        const utype m2  = utype(0x3333); //binary: 00110011..
        const utype m4  = utype(0x0f0f); //binary:  4 zeros,  4 ones ...
        const utype m8  = utype(0x00ff); //binary:  8 zeros,  8 ones ...
        // swap odd and even bits
        v = bitwise_or(bitwise_and(shr(v, 1), m1), shift_left(bitwise_and(v, m1), 1));
        // swap consecutive pairs
        v = bitwise_or(bitwise_and(shr(v, 2), m2), shift_left(bitwise_and(v, m2), 2));
        // swap nibbles ...
        v = bitwise_or(bitwise_and(shr(v, 4), m4), shift_left(bitwise_and(v, m4), 4));
        // swap bytes ...
        v = bitwise_or(bitwise_and(shr(v, 8), m8), shift_left(bitwise_and(v, m8), 8));
        return bitwise_cast<A0>(v);
        }
   };

   BOOST_DISPATCH_OVERLOAD_IF(reversebits_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::ints32_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        using utype = bd::as_integer_t<A0, unsigned>;
        utype v = bitwise_cast<utype>(a0);
        const utype m1  = utype(0x55555555); //binary: 0101...
        const utype m2  = utype(0x33333333); //binary: 00110011..
        const utype m4  = utype(0x0f0f0f0f); //binary:  4 zeros,  4 ones ...
        const utype m8  = utype(0x00ff00ff); //binary:  8 zeros,  8 ones ...
        const utype m16 = utype(0x0000ffff); //binary:  16 zeros,  16 ones ...
        // swap odd and even bits
        v = bitwise_or(bitwise_and(shr(v, 1), m1), shift_left(bitwise_and(v, m1), 1));
        // swap consecutive pairs
        v = bitwise_or(bitwise_and(shr(v, 2), m2), shift_left(bitwise_and(v, m2), 2));
        // swap nibbles ...
        v = bitwise_or(bitwise_and(shr(v, 4), m4), shift_left(bitwise_and(v, m4), 4));
        // swap bytes ...
        v = bitwise_or(bitwise_and(shr(v, 8), m8), shift_left(bitwise_and(v, m8), 8));
        // swap shorts ...
        v = bitwise_or(bitwise_and(shr(v, 16), m16), shift_left(bitwise_and(v, m16), 16));
        return bitwise_cast<A0>(v);
        }
   };
} } }

#endif

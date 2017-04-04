//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CORRECT_FMA_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/group.hpp>
#include <boost/simd/function/split.hpp>
#include <boost/simd/function/two_add.hpp>
#include <boost/simd/function/two_prod.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/function/pedantic.hpp>

#ifndef BOOST_SIMD_DONT_CARE_FMA_OVERFLOW
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/maxmag.hpp>
#include <boost/simd/function/minmag.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD_IF(fma_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pedantic_tag
                             , bs::pack_<bd::single_<A0>, X>
                             , bs::pack_<bd::single_<A0>, X>
                             , bs::pack_<bd::single_<A0>, X>
                             )
   {
      BOOST_FORCEINLINE A0 operator()( const pedantic_tag &
                                     , const A0& a0, const A0& a1, const A0& a2) const BOOST_NOEXCEPT
      {
        auto s0 = split(a0);
        auto s1 = split(a1);
        auto s2 = split(a2);
        return group(s0[0]*s1[0]+s2[0], s0[1]*s1[1]+s2[1]);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(fma_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const pedantic_tag &
                                     , const A0& a0, const A0& a1, const A0& a2) const BOOST_NOEXCEPT
      {
        A0 p, rp, s, rs;
  #ifndef BOOST_SIMD_DONT_CARE_FMA_OVERFLOW
        using iA0 = bd::as_integer_t<A0>;
        A0 amax =  a0; maxmag(a0, a1);
        A0 amin =  a1; minmag(a0, a1);
        iA0 e0 = -shift_right(exponent(amax), 1);
        amax = pedantic_(ldexp)(amax, e0);
        A0 a02 = pedantic_(ldexp)(a2, e0);
        std::tie(p, rp) = two_prod(amax, amin);
        std::tie(s, rs) = two_add(p, a02);
        return pedantic_(ldexp)(s+(rp+rs), -e0);
  #else
        std::tie(p, rp) = two_prod(a0, a1);
        std::tie(s, rs) = two_add(p, a2);
        return s+(rp+rs);
 #endif
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(fma_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_<bd::int_<A0>, X>
                          , bs::pack_<bd::int_<A0>, X>
                          , bs::pack_<bd::int_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const pedantic_tag &
                                     , const A0& a0, const A0& a1, const A0& a2) const BOOST_NOEXCEPT
      {
        // correct fma has to ensure "no intermediate overflow".
        // This is done in the case of signed integers by transtyping to unsigned type
        // to perform the computations in a guaranteed 2-complement environment
        // since signed integer overflow in C++ produces "undefined results"
        using utype =  bd::as_integer_t<A0>;
        return bitwise_cast<A0>(fma(bitwise_cast<utype>(a0), bitwise_cast<utype>(a1), bitwise_cast<utype>(a2)));
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF(fma_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_<bd::uint_<A0>, X>
                          , bs::pack_<bd::uint_<A0>, X>
                          , bs::pack_<bd::uint_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const pedantic_tag &
                                     , const A0& a0, const A0& a1, const A0& a2) const BOOST_NOEXCEPT
      {
        return a0*a1+a2;
      }
   };
} } }

#endif

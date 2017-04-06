//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_TRIG_BASE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_TRIG_BASE_HPP_INCLUDED
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/arch/common/detail/scalar/trig_reduction.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/constant/pio_4.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/quarter.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/deginrad.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/mtwo.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/config.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

// trigonometric functions are implemented using the classical cephes/fdlibm/libc principles
// however the formal reduce/eval/return is properly divided to allow choices versus
// speed, accuracy and  SIMD vectorisation
//
// On small ranges performance can be obtained with almost full accuracy (1 ulp) at 1 to 2
// cycles per element for a cosine computation using SIMD. But if one require full accuracy
// on the full float or double range, the prize can grow up to few hundreds of cycle for
// some big values of input.
// See the boost/simd technical documentation for more insights

namespace boost { namespace simd
{
  namespace detail
  {
    // in the class defined below:
    // A0 is the argument type of the trigonometric functions
    //
    // Up to now, only floating real based on IEEE 754 float or double are supported
    // (sorry no long double for lack of portability)

    template < typename A0, typename unit_tag> struct trig_ranges;
    template < typename A0>  struct trig_ranges<A0, tag::radian_tag>
    {
      static BOOST_FORCEINLINE A0    max_range() BOOST_NOEXCEPT {return Pio_4<A0>(); }
      static BOOST_FORCEINLINE A0    scale()     BOOST_NOEXCEPT {return One<A0>(); }
    };
    template < typename A0>  struct trig_ranges<A0, tag::pi_tag>
    {
      static BOOST_FORCEINLINE A0    max_range() BOOST_NOEXCEPT {return Quarter<A0>(); }
      static BOOST_FORCEINLINE A0    scale()     BOOST_NOEXCEPT {return Pi<A0>(); }
    };
    template < typename A0>  struct trig_ranges<A0, tag::degree_tag>
    {
      static BOOST_FORCEINLINE A0    max_range() BOOST_NOEXCEPT {return Ratio<A0, 45>(); }
      static BOOST_FORCEINLINE A0    scale()     BOOST_NOEXCEPT {return Deginrad<A0>(); }
    };


    // This class expose the public static members:
    // cosa     x -> cos(a*x)
    // sina     x -> sin(a*x)
    // tana     x -> tan(a*x)
    // cota     x -> cot(a*x)
    // sincosa  x -> cos(a*x) and sin(a*x)
    // "a" is not a run time parameter !
    // It stands as a remainder that according the Tag it can be considered
    // as a scale factor for the input of values:
    //   1           radian_tag,
    //   pi          pi_tag
    //   pi/180      degree_tag,
    // but the scaling is internal to the algorithm to provide better accuracy
    // and better performance.

    // It heritates of a reduction and an evaluation class to perform
    // the appropriate range reductions and function evaluations.

    // In this file stands the scalar version !
    // Some definitions are useless but provide facilities of comparaison with
    // the SIMD implementation
    //
    template < typename A0,
               typename unit_tag,
               typename style,
               typename mode =  tag::big_tag>
    struct trig_base{};

    template < typename A0,
               typename unit_tag,
               typename mode>
     struct trig_base<A0,unit_tag,tag::not_simd_type,mode>
     {
       using redu_t = trig_reduction<A0,unit_tag,tag::not_simd_type, mode>;
       using eval_t = trig_evaluation<A0,tag::not_simd_type>;
       using i_t    = bd::as_integer_t<A0, signed>;           // signed integer type associated to A0
       using style_t = typename mode::type;

       // for all functions the scalar algorithm is:
       // * quick return (or exception raising TODO) for inf and nan or specific invalid cases inputs
       // * range reduction
       // * computation of sign and evaluation selections flags
       // * evaluations
       // * return with flag based corrections

       static BOOST_FORCEINLINE A0 cosa(A0 a0){ return cosa(a0, style_t()); }
       static BOOST_FORCEINLINE A0 sina(A0 a0){ return sina(a0, style_t()); }
       static BOOST_FORCEINLINE A0 tana(A0 a0){ return tana(a0, style_t()); }
       static BOOST_FORCEINLINE A0 cota(A0 a0){ return cota(a0, style_t()); }
       static BOOST_FORCEINLINE std::pair<A0,A0> sincosa(const A0& a0){ return sincosa(a0,style_t()); }

       static BOOST_FORCEINLINE A0 cosa(A0 a0, const tag::regular&)
       {
         if (is_invalid(a0)) return Nan<A0>(); //Nan or Inf input
         const A0 x =  abs(a0);
         A0 xr = Nan<A0>();
         const i_t n = toint(redu_t::reduce(x, xr));
         const i_t swap_bit = n&One<i_t>();
         const i_t sign_bit = shift_left(bitwise_xor(swap_bit, (n&Two<i_t>())>>1), sizeof(i_t)*8-1);
         A0 z = sqr(xr);
         if (swap_bit)
           z = eval_t::sin_eval(z, xr);
         else
           z = eval_t::cos_eval(z);
         return bitwise_xor(z,sign_bit);
       }

       static BOOST_FORCEINLINE A0 sina(A0 a0, const tag::regular&) BOOST_NOEXCEPT
       {
         if (is_invalid(a0)) return Nan<A0>();
         const A0 x =  abs(a0);
         A0 xr = Nan<A0>();
         const i_t n = toint(redu_t::reduce(x, xr));
         const i_t swap_bit = n&One<i_t>();
         const A0 sign_bit = bitwise_xor(bitofsign(a0), shift_left(n&Two<i_t>(), sizeof(i_t)*8-2));
         A0 z = sqr(xr);
         if (swap_bit)
           z = eval_t::cos_eval(z);
         else
           z = eval_t::sin_eval(z, xr);
         return bitwise_xor(z,sign_bit);
       }

       static BOOST_FORCEINLINE A0 tana(A0 a0, const tag::regular&) BOOST_NOEXCEPT
       {
         if (is_invalid(a0)||redu_t::tan_invalid(a0)) return Nan<A0>();
         if (is_eqz(a0)) return a0;
         const A0 x =  abs(a0);
         A0 xr = Nan<A0>(), y;
         const i_t n = toint(redu_t::reduce(x, xr));
         y = eval_t::tan_eval(xr, 1-((n&1)<<1));
         // 1 -- n even
         //-1 -- n odd
         return bitwise_xor(y, bitofsign(a0));
       }

       static BOOST_FORCEINLINE A0 cota(A0 a0, const tag::regular&) BOOST_NOEXCEPT
       {
         if (is_invalid(a0)||redu_t::cot_invalid(a0)) return Nan<A0>();
         const A0 x = abs(a0);
         const A0 bos =  bitofsign(a0);
         if (!a0) return bitwise_or(Inf<A0>(), bos);
         A0 xr = Nan<A0>();
         const i_t n = toint(redu_t::reduce(x, xr));
         const A0 y = eval_t::cot_eval(xr, 1-((n&1)<<1));
         return bitwise_xor(y, bos);
       }

       static BOOST_FORCEINLINE std::pair<A0,A0> sincosa(A0 a0, const tag::regular&) BOOST_NOEXCEPT
       {
         A0 s, c;
         if (is_invalid(a0)) return {Nan<A0>(), Nan<A0>()};
         const A0 x =  abs(a0);
         constexpr i_t de = static_cast<i_t>(sizeof(i_t)*8-1);
         A0 xr;
         const i_t n = toint(redu_t::reduce(x, xr));
         const i_t swap_bit = n&One<i_t>();
         const A0 z = sqr(xr);
         const i_t cos_sign_bit = shift_left(bitwise_xor(swap_bit, (n&Two<i_t>())>>1), de);
         const A0 sin_sign_bit = bitwise_xor(bitofsign(a0), shift_left(n&Two<i_t>(), de-1));

         if (is_nez(swap_bit))
         {
           c = eval_t::sin_eval(z, xr);
           s = eval_t::cos_eval(z);
         }
         else
         {
           c = eval_t::cos_eval(z);
           s = eval_t::sin_eval(z, xr);
         }
         return {bitwise_xor(s,sin_sign_bit), bitwise_xor(c,cos_sign_bit)};
       }

       static BOOST_FORCEINLINE A0 cosa(A0 a0, const tag::restricted &) BOOST_NOEXCEPT
       {
         A0 x =  scale(a0);
         if(not_in_range(a0))
           return Nan<A0>();
         else
           return eval_t::cos_eval(sqr(x));
       }


       static BOOST_FORCEINLINE A0 sina(A0 a0, const tag::restricted&) BOOST_NOEXCEPT
       {
         if (is_eqz(a0)) return a0;
         A0 x =  scale(a0);
         if(not_in_range(a0))
           return Nan<A0>();
         else
           return eval_t::sin_eval(sqr(x), x);
       }

       static BOOST_FORCEINLINE A0 tana(A0 a0, const tag::restricted&) BOOST_NOEXCEPT
       {
         if (is_eqz(a0)) return a0;
         A0 x =  scale(a0);
         if(not_in_range(a0))
           return Nan<A0>();
         else
           return eval_t::base_tan_eval(x);
       }

       static BOOST_FORCEINLINE A0 cota(A0 a0, const tag::restricted&) BOOST_NOEXCEPT
       {
         if (is_eqz(a0)) return rec(a0);
          if(not_in_range(a0))
           return Nan<A0>();
          else
          {

            A0 x =  scale(a0);
            return rec(eval_t::base_tan_eval(x));
          }
       }

       static BOOST_FORCEINLINE std::pair<A0, A0>sincosa(A0 a0, const tag::restricted&) BOOST_NOEXCEPT
       {
         if (is_eqz(a0))       return {a0, One<A0>()} ;
         if(not_in_range(a0))  return {Nan<A0>(), Nan<A0>()};
         A0 x =  scale(a0);
         A0 z =  sqr(x);
         return { eval_t::sin_eval(z, x), eval_t::cos_eval(z)};
       }

       static BOOST_FORCEINLINE bool not_in_range(A0 a0) BOOST_NOEXCEPT
       {
         return bs::abs(a0) > trig_ranges<A0,unit_tag>::max_range();
       }
       static BOOST_FORCEINLINE A0 scale (A0 a0) BOOST_NOEXCEPT
       {
         return a0*trig_ranges<A0,unit_tag>::scale();
       }
    };
  }
} }
#endif

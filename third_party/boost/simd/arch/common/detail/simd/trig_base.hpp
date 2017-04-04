//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_TRIG_BASE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_TRIG_BASE_HPP_INCLUDED

#include <boost/simd/arch/common/detail/simd/trig_reduction.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/if_allbits_else_zero.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/detail/constant/maxleftshift.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/mtwo.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;

    template < class A0, class unit_tag, class mode>
    struct trig_base < A0, unit_tag,  tag::simd_type, mode>
    {
      typedef typename bs::as_logical_t<A0>                        bA0; // logical type associated to A0
      typedef trig_reduction<A0,unit_tag, tag::simd_type, mode> redu_t;
      typedef trig_evaluation<A0,tag::simd_type>                eval_t;
      typedef typename bd::scalar_of<A0>::type                     sA0; // scalar version of A0
      typedef typename bd::as_integer<A0, signed>::type       int_type; // signed integer type associated to A0
      typedef typename bs::as_logical<int_type>::type        bint_type; // logical type associated to int_type
      typedef typename bd::scalar_of<int_type>::type         sint_type; // scalar version of the associated type
      typedef typename mode::type                                style;

      // for all functions the scalar algorithm is:
      // * range reduction
      // * computation of sign and evaluation selections flags
      // * evaluations of the two branches and selection using flags
      // * return with flag based corrections and inf and nan or specific invalid cases inputs considerations

      static BOOST_FORCEINLINE A0 cosa(const A0& a0){ return cosa(a0, style()); }
      static BOOST_FORCEINLINE A0 sina(const A0& a0){ return sina(a0, style()); }
      static BOOST_FORCEINLINE A0 tana(const A0& a0){ return tana(a0, style()); }
      static BOOST_FORCEINLINE A0 cota(const A0& a0){ return cota(a0, style()); }
      static BOOST_FORCEINLINE std::pair<A0,A0> sincosa(const A0& a0){ return sincosa(a0,style()); }

    private:
      static BOOST_FORCEINLINE A0 cosa(const A0& a0, const tag::restricted&)
      {
        const A0 x =  scale(a0);
        return  eval_t::cos_eval(sqr(x));
      }

      static BOOST_FORCEINLINE A0 cosa(const A0& a0, const tag::regular&)
      {
        const A0 x = bs::abs(a0);
        A0 xr = Nan<A0>();
        A0 n =  redu_t::reduce(x, xr);
        auto tmp = if_one_else_zero(n >= Two<A0>());
        auto swap_bit = (fma(Mtwo<A0>(), tmp, n));
        auto sign_bit = if_else_zero(bitwise_xor(swap_bit, tmp), Signmask<A0>());
        A0 z = sqr(xr);
        A0 se = eval_t::sin_eval(z, xr);
        A0 ce = eval_t::cos_eval(z);
        A0 z1 = if_else(is_nez(swap_bit), se, ce);
        return bitwise_xor(z1, sign_bit);
      }

      static BOOST_FORCEINLINE A0 sina(const A0& a0_n, const tag::restricted&)
      {
        A0 x =   scale(a0_n);
        A0 se = eval_t::sin_eval(sqr(x), x);
        return se;
      }

      static BOOST_FORCEINLINE A0 sina(const A0& a0, const tag::regular&)
      {
        const A0 x = bs::abs(a0);
        A0 xr = Nan<A0>();
        const A0 n = redu_t::reduce(x, xr);
        auto tmp = if_one_else_zero(n >= Two<A0>());
        auto swap_bit = (fma(Mtwo<A0>(), tmp, n));
        auto sign_bit = bitwise_xor(bitofsign(a0), if_else_zero(tmp, Signmask<A0>()));
        const A0 z = sqr(xr);
        const A0 se = eval_t::sin_eval(z, xr);
        const A0 ce = eval_t::cos_eval(z);
        const A0 z1 = if_else(is_eqz(swap_bit), se, ce);
        return bitwise_xor(z1, sign_bit);
      }

      static BOOST_FORCEINLINE A0 tana(const A0& a0, const tag::restricted&)
      {
        return eval_t::base_tancot_eval(scale(a0));
      }

      static BOOST_FORCEINLINE A0 tana(const A0& a0, const tag::regular&)
      {
        A0 x =  bs::abs(a0);
        A0 xr = Nan<A0>();
        A0 n = redu_t::reduce(x, xr);
        auto tmp = if_one_else_zero( n >= Two<A0>());
        auto swap_bit = (fma(Mtwo<A0>(), tmp, n));
        auto test = is_eqz(swap_bit);
        const A0 y = eval_t::tan_eval(xr, test);
        auto testnan = redu_t::tan_invalid(a0);
        return if_nan_else(testnan, bitwise_xor(y, bitofsign(a0)));
      }

      static BOOST_FORCEINLINE A0 cota(const A0& a0, const tag::restricted&)
      {
        return eval_t::base_tancot_eval(scale(a0));
      }

      static BOOST_FORCEINLINE A0 cota(const A0& a0, const tag::regular&)
      {
        const A0 x = bs::abs(a0);
        A0 xr = Nan<A0>();
        const A0 n = redu_t::reduce(x, xr);
        auto tmp = if_one_else_zero( n >= Two<A0>());
        auto swap_bit = (fma(Mtwo<A0>(), tmp, n));
        auto test = is_eqz(swap_bit);
        const A0 y = eval_t::cot_eval(xr, test);
        const bA0 testnan = redu_t::cot_invalid(a0);
        // this if_else is normally not needed but with clang the zero value if erroneous
        // if not there !
        return if_else(is_nez(a0), if_nan_else(testnan
                                              , bitwise_xor(y, bitofsign(a0))), rec(a0));
      }

      // simultaneous cosa and sina function
      static BOOST_FORCEINLINE std::pair<A0, A0> sincosa(const A0& a0, const tag::restricted&)
      {
        A0 x =  scale(a0);
        A0 z =  sqr(x);
        return {eval_t::sin_eval(z, x), eval_t::cos_eval(z)};
      }

      static BOOST_FORCEINLINE  std::pair<A0, A0> sincosa(const A0& a0, const tag::regular&)
      {
        A0 x =  bs::abs(a0);
        A0 xr = Nan<A0>();
        A0 n = redu_t::reduce(x, xr);
        auto tmp = if_one_else_zero(n >= Two<A0>());
        auto swap_bit = (fma(Mtwo<A0>(), tmp, n));
        auto cos_sign_bit = if_else_zero(bitwise_xor(swap_bit, tmp), Signmask<A0>());
        auto sin_sign_bit = bitwise_xor(bitofsign(a0),if_else_zero(tmp, Signmask<A0>()));

        A0 z = bs::sqr(xr);
        A0 t1 = eval_t::sin_eval(z, xr);
        A0 t2 = eval_t::cos_eval(z);
        auto test = is_nez(swap_bit);
        return { bitwise_xor(if_else(test, t2, t1),sin_sign_bit)
               , bitwise_xor(if_else(test, t1, t2),cos_sign_bit) };
      }

      static BOOST_FORCEINLINE A0 scale(const A0& a0)
      {
        return if_nan_else(is_greater(bs::abs(a0),
                              trig_ranges<A0,unit_tag>::max_range()), a0)
          *trig_ranges<A0,unit_tag>::scale();
      }

    };
  }
} }


#endif

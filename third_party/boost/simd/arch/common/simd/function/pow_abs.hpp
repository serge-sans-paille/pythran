//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_POW_ABS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_POW_ABS_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/log2_em1.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/detail/constant/powlargelim.hpp>
#include <boost/simd/detail/constant/powlowlim.hpp>
#include <boost/simd/constant/sixteen.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/ifrexp.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/if_else_nan.hpp>
#include <boost/simd/function/if_one_else_zero.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_odd.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/log.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/pow2.hpp>
#include <boost/simd/function/if_inc.hpp>
#include <boost/simd/function/if_minus.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/signnz.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <utility>


#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/mzero.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/if_zero_else_one.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/is_ltz.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF( pow_abs_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>, X>
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    inline A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      using iA0 = bd::as_integer_t<A0>;
      iA0 e;
      A0 ax = bs::abs(a0);
      A0 x;
      std::tie(x, e) = pedantic_(ifrexp)(ax);
      iA0 i  = detail::pow_kernel<A0>::select(x);
      A0 z = sqr(x);
      A0 w = detail::pow_kernel<A0>::pow1(x, z);
      w = fma(Mhalf<A0>(), z, w);
      w = fma(Log2_em1<A0>(), w, w);
      z = fma(Log2_em1<A0>(), x, w);
      z += x;
      w =  fma(tofloat(-i), Ratio<A0, 1, 16>(), tofloat(e));
      A0 ya = reduc(a1);
      A0 yb = a1 - ya;
      A0 W = fma(z, a1, w*yb);
      A0 Wa = reduc(W);
      A0 Wb = W - Wa;
      W = fma(w, ya, Wa);
      Wa = reduc(W);
      A0 u = W - Wa;
      W = Wb + u;
      Wb = reduc(W);
      w = Sixteen<A0>()*(Wa + Wb);
      // Test the power of 2 for over/underflow
      auto inf_ret = is_greater(w, Powlargelim<A0>());
      auto zer_ret = is_less(w, Powlowlim<A0>());
      e = toint(w);
      Wb = W - Wb;
      auto test = is_gtz(Wb);
      e = if_inc(test, e);
      Wb = if_minus(test, Wb, Ratio<A0, 1, 16>());
      z = detail::pow_kernel<A0>::pow2(Wb)*Wb;
      i = if_inc(is_gtz(e), (e/Sixteen<iA0>()));
      e = (i*Sixteen<iA0>()) - e;
      w =  detail::pow_kernel<A0>::twomio16(e);
      z = fma(w, z, w);
      z = pedantic_(ldexp)( z, i );
#ifndef BOOST_SIMD_NO_INFINITIES
      auto gtax1 = is_greater(ax,One<A0>());
      z =  if_else(is_equal(a1,  Inf<A0>()),if_else_zero(gtax1, Inf<A0>()), z);
      z =  if_else(is_equal(a1, Minf<A0>()),if_zero_else(gtax1, Inf<A0>()), z);
      z =  if_else(is_equal(ax, Inf<A0>()),
                   if_else(is_gtz(a1),
                           Inf<A0>(),
                           if_zero_else_one(is_ltz(a1))),
                   z);
#endif
      z = if_zero_else(zer_ret, z);
      z = if_else(inf_ret, Inf<A0>(), z);
      z = if_else(is_equal(ax, One<A0>()), ax, z);

      z = if_else(is_eqz(a0),
                  if_else(is_ltz(a1), bs::Inf<A0>(),
                          if_one_else_zero(is_eqz(a1))
                         ),
                  z
                 );
#ifndef BOOST_SIMD_NO_NANS
      z = if_else(is_nan(a0),
                  if_else_nan(is_eqz(a1), One<A0>()),
                  z
                 );
#endif
      return z;
    }
  private :
    static BOOST_FORCEINLINE A0 reduc(const A0& x)
    {
      // Find a multiple of 1/16 that is within 1/16 of x.
      return Ratio<A0, 1, 16>()*floor(Sixteen<A0>()*x);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( pow_abs_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::raw_tag
                             , bs::pack_< bd::floating_<A0>, X>
                             , bs::pack_< bd::floating_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator()(const raw_tag &,
                                    A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      return bs::exp(a1*bs::log(bs::abs(a0)));
    }
  };
} } }


#endif

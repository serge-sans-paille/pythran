//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_ACOS_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_COMPLEX_GENERIC_ACOS_HPP_INCLUDED
#include <nt2/trigonometric/functions/acos.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/sdk/complex/meta/as_dry.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/acos.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/logical_notand.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/is_greater_equal.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_inf.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_not_nan.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/atan.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/negif.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/safe_max.hpp>
#include <nt2/include/functions/safe_min.hpp>


#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/smallestposval.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/pio_2.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acos_, tag::cpu_, (A0)
                            , (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      //
      // This implementation is a simd transcription and adaptation of the boost_math code
      // which itself is a transcription of the pseudo-code in:
      //
      // "Implementing the complex Arcsine and Arccosine Functions using Exception Handling."
      // T E Hull, Thomas F Fairgrieve and Ping Tak Peter Tang.
      // ACM Transactions on Mathematical Software, Vol 23, No 3, Sept 1997.
      //
      typedef typename meta::as_real<A0>::type rtype;
      typedef typename meta::as_logical<rtype>::type ltype;
      const rtype a_crossover = splat<rtype>(1.5);
      const rtype b_crossover = splat<rtype>(0.6417);
      ltype  ltzra0 = is_ltz(nt2::real(a0));
      ltype  gtzia0 = is_gtz(nt2::imag(a0));
      //
      // Begin by insuring nt2::real(a0) >= 0 and nt2::imag(a0) >= 0 :
      //
      rtype x = nt2::abs(nt2::real(a0));
      rtype y = nt2::abs(nt2::imag(a0));
      rtype proper_real = nt2::acos(x);
      ltype lexone = le(x, One<rtype>());
      ltype is_proper_real = logical_and(is_real(a0), lexone);

      const rtype s_max = safe_max(Eight<rtype>());
      const rtype s_min = safe_min(Four<rtype>());
      rtype xp1 =  oneplus(x);
      rtype xm1 =  minusone(x);
      ltype not_in_safe_zone = logical_or(logical_or(gt(x,s_max), lt(x,s_min)),
                                          logical_or(gt(y,s_max), lt(y,s_min)));
      //compute for safe zone
      rtype r, i;
      rtype yy = sqr(y);
      rtype tr = nt2::sqrt(sqr(xp1) + yy);
      rtype ts = nt2::sqrt(sqr(xm1) + yy);
      rtype a = Half<rtype>()*(tr + ts);
      rtype b = x/a;
      //compute r for b >  b_crossover
      rtype apx = a + x;
      r = if_else(lexone,
                  nt2::atan(nt2::sqrt(Half<rtype>()*apx*(yy/(tr+xp1)+(ts-xm1)))/x),
                  nt2::atan((y*nt2::sqrt(Half<rtype>()*(apx/(tr+xp1)+apx/(ts+xm1))))/x)
        );
      // r is computed
      r = if_else(le(b, b_crossover), nt2::acos(b), r);
      //compute am1 temporary for i for a <= a_crossover
      rtype tmp = yy/(tr+xp1);
      rtype am1 = if_else(lexone,
                          Half<rtype>()*(tmp+yy/(ts-xm1)),
                          Half<rtype>()*(tmp+(ts+xm1)));
      i =  if_else(le(a, a_crossover),
                   nt2::log1p(am1 + nt2::sqrt(am1*(oneplus(a)))),
                   nt2::log(a + nt2::sqrt(minusone(sqr(a))))
        );
      // i is computed
      //compute for exception zone
      if (nt2::any(not_in_safe_zone))
      {
        ltype zone1 =  le(y, nt2::Eps<rtype>()*nt2::abs(xm1));
        if (nt2::any(logical_and(zone1, not_in_safe_zone)))
        {
          rtype rr = if_else(lexone, nt2::acos(x), Zero<rtype>());
          rtype ii = if_else(lexone, y/nt2::sqrt(-xp1*xm1),
                             if_else(gt(Valmax<rtype>()/xp1, xm1),
                                     nt2::log1p(xm1 + nt2::sqrt(xp1*xm1)),
                                     Log_2<rtype>() + nt2::log(x)
                               )
            );
          r = if_else(zone1, rr, r);
          i = if_else(zone1, ii, i);
        }
        ltype zone2 = le(y, s_min);
        ltype not_treated = logical_notand(zone1, not_in_safe_zone);
        if (nt2::any(logical_and(zone2, not_treated)))
        {
          rtype sqrty =  nt2::sqrt(y);
          r = if_else(zone2, sqrty, r);
          i = if_else(zone2, sqrty, i);
        }
        ltype zone3 = ge(minusone(Eps<rtype>()*y), x);
        not_treated = logical_notand(zone2, not_treated);
        if (nt2::any(logical_and(zone3, not_treated)))
        {
          r = if_else(zone3,  Pio_2<rtype>(), r);
          i = if_else(zone3,  Log_2<rtype>() + nt2::log(y), i);
        }
        ltype zone4 = gt(x, One<rtype>());
        not_treated = logical_notand(zone3, not_treated);
        if (nt2::any(logical_and(zone4, not_treated)))
        {
          r = if_else(zone4, nt2::atan(y/x), r);
          i = if_else(zone4, Log_2<rtype>() + nt2::log(y) + Half<rtype>()*nt2::log1p(sqr(x/y)), i);
        }
        not_treated = logical_notand(zone4, not_treated);
        if (nt2::any(not_treated))
        {
          rtype aa = nt2::sqrt(oneplus(sqr(y)));
          r = if_else(not_treated, Pio_2<rtype>(), r);
          i = if_else(not_treated, Half<rtype>()*nt2::log1p(Two<rtype>()*y*(y+aa)), i);
        }
      }
      if (nt2::any(is_invalid(a0)))
      {
        ltype nanx = is_nan(x);
        ltype nany = is_nan(y);
        ltype infx = eq(x, Inf<rtype>()) ;
        ltype infy = eq(y, Inf<rtype>()) ;
        if (nt2::any(infx))
        {
          r =  if_else(infx, Zero<rtype>(), r);
          i =  if_else(infx, Inf<rtype>(), i);
          r =  if_else(logical_and(infx, infy), Pi<rtype>()/Four<rtype>(), r);
          i =  if_else(logical_and(infx, infy), Inf<rtype>(), i);//**
                                                                     r =  if_else(logical_and(infx, nany), y, r);
          i =  if_else(logical_and(infx, nany), Minf<rtype>(), i);
        }
        if (nt2::any(nanx))
        {
          r =  if_else(nanx, x, r);
          i =  if_else(nanx, x, i);
          i =  if_else(logical_and(nanx, infy), y, i);
        }
        ltype test = logical_notand(logical_or(infx, nanx), infy);
        if (nt2::any(test))
        {
          r = if_else(logical_and(infy, test), Pio_2<rtype>(), r);
          i = if_else(logical_and(infy, test), y, i); //**
                                                          }
        test = logical_notand(logical_or(infx, nanx), nany);
        r = if_else(test,if_else(is_imag(a0), Pio_2<rtype>(), y), r);
        i = if_else(test,y,i);
      }
      // use proper real results
      r = if_else(is_proper_real, proper_real,   r);
      i = if_else(is_proper_real, Zero<rtype>(), i);
      // restore signs
      r = if_else(ltzra0, Pi<rtype>()-r, r);
      i = negif(gtzia0, i);
      result_type res = result_type(r, i);
      return res;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::acos_, tag::cpu_, (A0)
                              , (generic_< dry_< arithmetic_<A0> > >)
    )
  {
    typedef typename meta::as_real<A0>::type rtype;
    typedef typename meta::as_complex<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      //TODO optimize it
      if (nt2::all(is_real(a0)) && nt2::all(le(nt2::abs(a0), One<rtype>())))
        return result_type(nt2::acos(nt2::real(a0)));
      return nt2::acos(result_type(nt2::real(a0), Zero<rtype>()));
    }
  };

} }

#endif

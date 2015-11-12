//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_GAMMAINC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_GAMMAINC_HPP_INCLUDED

#include <nt2/euler/functions/gammainc.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/max.hpp>
#include <nt2/include/functions/simd/min.hpp>
#include <nt2/include/functions/simd/maximum.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/gammaln.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/logical_not.hpp>
#include <nt2/include/functions/simd/eps.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/hundred.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::gammainc_, tag::cpu_,
                             (A0)(X),
                             ((simd_<floating_<A0>,X>))
                             ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    typedef typename meta::as_logical<A0>::type bA0;

    BOOST_FORCEINLINE result_type operator()(const A0& xx, const A0& aa) const
    {
      A0 x = xx, a = aa;
      const A0 amax = nt2::splat<A0>(1048576);

      bA0 test = gt(a, amax);

      std::size_t nb = nt2::inbtrue(test);

      if(nb)
      {
        x =  nt2::max ( nt2::fma( nt2::sqrt(amax/a)
                                , x-(a-nt2::Third<A0>())
                                , amax-nt2::Third<A0>()
                                )
                      , Zero<A0>()
                      );

        a =  nt2::if_else(test, amax, a);
      }

      A0 res = nt2::Nan<A0>();
      std::size_t nbt = 0u;
      test = nt2::lt(x, nt2::oneplus(a));

      nb = boost::simd::inbtrue(test);
      if(nb)
      {
        res = nt2::if_else(test, lower_gammainc(x, a, test), res);
        nbt+= nb;

        if (nbt >= meta::cardinal_of<A0>::value)
          return res;
      }

      test = nt2::logical_not(test);
      res = boost::simd::if_else( test
                                , upper_gammainc(x, a, test)
                                , res
                                );
      return res;
    }

    private:

    static BOOST_FORCEINLINE result_type
    lower_gammainc(A0 const& a0, A0 const& a1, bA0 const& test)
    {
      typedef typename boost::dispatch::meta::scalar_of<A0>::type sA0;

      // insure convergence in each case for all members of simd vector
      // making x =  a <  a+1 when the test do not succeed
      A0 const x = nt2::if_else(test, a0, a1);

      //Series expansion for x < a+1
      A0 ap  = a1;
      A0 del = One<A0>();
      A0 sum = del;

      while (     nt2::maximum(nt2::abs(del))
              >=  Hundred<sA0>()*nt2::eps(nt2::maximum(nt2::abs(sum)))
            )
      {
        ap  +=One<A0>();
        del  = x*del/ap;
        sum += del;
      }

      A0 b = sum*nt2::exp(-x + a1*nt2::log(x) - nt2::gammaln(oneplus(a1)));

      //  For very small a, the series may overshoot very slightly.
      b =  nt2::min(b, One<A0>());

      //  if lower, b(k) = bk; else b(k) = 1-bk; end
      return b;
    }

    static BOOST_FORCEINLINE result_type
    upper_gammainc(A0 const& a0, A0 const& a1, bA0 const& test)
    {
      typedef typename boost::dispatch::meta::scalar_of<A0>::type sA0;

      // insure convergence in each case for all members of simd vector
      // making x =  a <  a+1 when the test do not succeed
      A0 const x = nt2::if_else(test, a0, oneplus(a1));

      // Continued fraction for x >= a+1
      //k = find(a ~= 0 & x >= a+1); % & x ~= 0
      A0 x0 = One<A0>();
      A0 x1 = x;
      A0 b0 = Zero<A0>();
      A0 b1 = x0;
      A0 fac = nt2::rec(x1);
      A0 n = One<A0>();
      A0 g = b1*fac;
      A0 gold = b0;

      while (   maximum(nt2::abs(g-gold))
            >=  Hundred<sA0>()*nt2::eps(nt2::maximum(nt2::abs(g)))
            )
      {
        gold = g;
        A0 ana = n - a1;
        x0 = (x1 + x0*ana)* fac;
        b0 = (b1 + b0*ana)* fac;
        A0 anf = n*fac;
        x1 = x * x0 + anf * x1;
        b1 = x * b0 + anf * b1;
        fac = nt2::rec(x1);
        g = b1 * fac;
        n = oneplus(n);
      }

      return if_else( nt2::is_inf(x)
                    , One<A0>()
                    , oneminus(nt2::exp(-x + a1*nt2::log(x) - gammaln(a1))*g)
                    );
    }
  };
} }
#endif

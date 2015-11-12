//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_GAMMA_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_GAMMA_HPP_INCLUDED

#include <nt2/euler/functions/gamma.hpp>
#include <nt2/euler/functions/details/gamma_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pi.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/floor.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_even.hpp>
#include <nt2/include/functions/simd/is_flint.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/functions/simd/selsub.hpp>
#include <nt2/include/functions/simd/sinpi.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/stirling.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#endif

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::gamma_, tag::cpu_,
                             (A0)(X),
                             ((simd_<floating_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    typedef typename meta::as_logical<A0>::type bA0;
    NT2_FUNCTOR_CALL(1)
    {
      bA0 nan_result = logical_and(is_ltz(a0), is_flint(a0));
      #ifndef BOOST_SIMD_NO_INVALIDS
      nan_result = logical_or(nt2::is_nan(a0), nan_result);
      #endif
      A0 q = nt2::abs(a0);
      bA0 test = lt(a0, nt2::splat<A0>(-33.0));
      std::size_t nb = nt2::inbtrue(test);
      A0 r =  Nan<A0>();
      if(nb > 0)
      {
        //treat negative large with reflection
        r = large_negative(q);
        if (nb >= meta::cardinal_of<A0>::value)
          return nt2::if_nan_else(nan_result, r);
      }
      A0 r1 = other(a0, test);
      A0 r2 = if_else(test, r, r1);
      return nt2::if_nan_else(nan_result, r2);
    }

  private :
    static inline A0 large_negative(const A0& q)
    {
      A0 st =  nt2::stirling(q);
      A0 p = nt2::floor(q);
      A0 sgngam = nt2::negif(nt2::is_even(p), One<A0>());
      A0 z = q - p;
      bA0 test2 = lt(z, nt2::Half<A0>() );
      z = nt2::selsub(test2, z, nt2::One<A0>());
      z = q*nt2::sinpi(z);
      z =  nt2::abs(z);
      return sgngam*nt2::Pi<A0>()/(z*st);
    }

    static inline A0 other(const A0& q, const bA0& test)
    {
      A0 x =  nt2::if_else(test, Two<A0>(), q);
      #ifndef BOOST_SIMD_NO_INFINITIES
      bA0 inf_result = eq(q, Inf<A0>());
      x = if_else(inf_result, Two<A0>(), x);
      #endif
      A0 z = nt2::One<A0>();
      bA0 test1 = ge(x,Three<A0>());
      while( nt2::any(test1) )
      {
        x = nt2::seladd(test1, x, nt2::Mone<A0>());
        z = nt2::if_else(   test1, z*x, z);
        test1 = ge(x,Three<A0>());
      }
      //all x are less than 3
      test1 = nt2::is_ltz(x);
      while( nt2::any(test1) )
      {
        z = nt2::if_else(test1, z/x, z);
        x = nt2::seladd(test1, x, nt2::One<A0>());
        test1 = nt2::is_ltz(x);
      }
      //all x are greater than 0 and less than 3
      bA0 test2 = lt(x,nt2::Two<A0>());
      while( nt2::any(test2))
      {
        z = nt2::if_else(test2, z/x, z);
        x = nt2::seladd(test2, x, nt2::One<A0>());
        test2 = lt(x,nt2::Two<A0>());
      }
      //all x are greater equal 2 and less than 3
      x = z*details::gamma_kernel<A0>::gamma1(x-nt2::Two<A0>());
      #ifndef BOOST_SIMD_NO_INFINITIES
      return if_else(inf_result, q, x);
      #else
      return x;
      #endif
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_CBRT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SIMD_COMMON_CBRT_HPP_INCLUDED

#include <nt2/exponential/functions/cbrt.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_or.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/fast_frexp.hpp>
#include <nt2/include/functions/simd/fast_ldexp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/is_gez.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/negate.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

#ifndef BOOST_SIMD_NO_DENORMALS
#include <nt2/include/constants/smallestposval.hpp>
#include <nt2/include/constants/twotomnmbo_3.hpp>
#include <nt2/include/constants/twotonmb.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#endif

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/functions/simd/is_inf.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cbrt_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0, signed>::type int_type;
      typedef typename meta::scalar_of<A0>::type             stype;
      typedef typename meta::as_logical<int_type>::type     b_type;
      A0 z =  nt2::abs(a0);
#ifndef BOOST_SIMD_NO_DENORMALS
      typedef typename meta::as_logical<A0>::type             b_A0;
      b_A0 denormal = lt(z, Smallestposval<A0>());
      z = if_else(denormal, z*Twotonmb<A0>(), z);
      A0 f = if_else(denormal, Twotomnmbo_3<A0>(), One<A0>());
#endif
      const A0 CBRT2  = double_constant< A0, 0x3ff428a2f98d728bll> ();
      const A0 CBRT4  = double_constant< A0, 0x3ff965fea53d6e3dll> ();
      const A0 CBRT2I = double_constant< A0, 0x3fe965fea53d6e3dll> ();
      const A0 CBRT4I = double_constant< A0, 0x3fe428a2f98d728bll> ();
      int_type e;
      A0  x = fast_frexp(z, e);
      x = horner < NT2_HORNER_COEFF_T(stype, 5,
                            (0xbfc13c93386fdff6ll,
                             0x3fe17e1fc7e59d58ll,
                             0xbfee8a4ca3ba37b8ll,
                             0x3ff23d6ee505873all,
                             0x3fd9c0c12122a4fell)
                            ) > (x);
      const b_type flag = is_gez(e);
      int_type e1 =  nt2::abs(e);
      int_type rem = e1;
      e1 /= Three<int_type>();
      rem -= e1*Three<int_type>();
      e =  negate(e1, e);
      const A0 cbrt2 = if_else(flag, CBRT2, CBRT2I);
      const A0 cbrt4 = if_else(flag, CBRT4, CBRT4I);
      A0 fact = if_else(is_equal(rem, One<int_type>()), cbrt2, One<A0>());
      fact = if_else(is_equal(rem, Two<int_type>()), cbrt4, fact);
      x = fast_ldexp(x*fact, e);
      x -= (x-z/sqr(x))*Third<A0>();
      x -= (x-z/sqr(x))*Third<A0>(); //two newton passes
#ifndef BOOST_SIMD_NO_DENORMALS
      x = b_or(x, bitofsign(a0))*f;
#else
      x = b_or(x, bitofsign(a0));
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
      return if_else(l_or(is_eqz(a0),is_inf(a0)), a0, x);
#else
      return if_else(is_eqz(a0), a0, x);
#endif
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cbrt_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 z =  nt2::abs(a0);
      typedef typename meta::as_integer<A0, signed>::type int_type;
      typedef typename meta::scalar_of<A0>::type             stype;
      typedef typename meta::as_logical<int_type>::type     b_type;
#ifndef BOOST_SIMD_NO_DENORMALS
      typedef typename meta::as_logical<A0>::type             b_A0;
      b_A0 denormal = lt(z, Smallestposval<A0>());
      z = if_else(denormal, z*Twotonmb<A0>(), z);
      A0 f = if_else(denormal, Twotomnmbo_3<A0>(), One<A0>());
#endif
      const A0 CBRT2  = single_constant< A0, 0x3fa14518> ();
      const A0 CBRT4  = single_constant< A0, 0x3fcb2ff5> ();
      const A0 CBRT2I = single_constant< A0, 0x3f4b2ff5> ();
      const A0 CBRT4I = single_constant< A0, 0x3f214518> ();
      int_type e;
      A0 x = fast_frexp(z, e);
      x = horner < NT2_HORNER_COEFF_T(stype, 5,
                            (0xbe09e49a,
                             0x3f0bf0fe,
                             0xbf745265,
                             0x3f91eb77,
                             0x3ece0609)
                            ) > (x);
      const b_type flag = is_gez(e);
      int_type e1 =  nt2::abs(e);
      int_type rem = e1;
      e1 /= Three<int_type>();
      rem -= e1*Three<int_type>();
      e = negate(e1, e);

      const A0 cbrt2 = if_else(flag, CBRT2, CBRT2I);
      const A0 cbrt4 = if_else(flag, CBRT4, CBRT4I);
      A0 fact = if_else(is_equal(rem, One<int_type>()), cbrt2, One<A0>());
      fact = if_else(is_equal(rem, Two<int_type>()), cbrt4, fact);
      x = fast_ldexp(x*fact, e);
      x -= (x-z/sqr(x))*Third<A0>();
#ifndef BOOST_SIMD_NO_DENORMALS
      x = b_or(x, bitofsign(a0))*f;
#else
      x = b_or(x, bitofsign(a0));
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
      return if_else(l_or(is_eqz(a0),is_inf(a0)), a0, x);
#else
      return if_else(is_eqz(a0), a0, x);
#endif
    }
  };
} }

#endif

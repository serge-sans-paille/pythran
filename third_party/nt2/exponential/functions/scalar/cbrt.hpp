//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_CBRT_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_CBRT_HPP_INCLUDED

#include <nt2/exponential/functions/cbrt.hpp>
#include <boost/simd/sdk/config.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/third.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/bitofsign.hpp>
#include <nt2/include/functions/scalar/bitwise_or.hpp>
#include <nt2/include/functions/scalar/fast_frexp.hpp>
#include <nt2/include/functions/scalar/fast_ldexp.hpp>
#include <nt2/include/functions/scalar/is_gez.hpp>
#include <nt2/include/functions/scalar/negate.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/as_integer.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#endif

#ifndef BOOST_SIMD_NO_DENORMALS
#include <nt2/include/constants/smallestposval.hpp>
#include <nt2/include/constants/twotomnmbo_3.hpp>
#include <nt2/include/constants/twotonmb.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cbrt_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 z =  nt2::abs(a0);
#ifndef BOOST_SIMD_NO_INFINITIES
      if (z == nt2::Inf<A0>() || (z == 0)) return a0;
#else
      if (z == 0) return a0;
#endif
#ifndef BOOST_SIMD_NO_DENORMALS
      A0 f = One<A0>();
      if (z < Smallestposval<A0>())
      {
        z *= Twotonmb<A0>();
        f  = Twotomnmbo_3<A0>();
      }
#endif
      const A0 CBRT2  = double_constant< A0, 0x3ff428a2f98d728bll> ();
      const A0 CBRT4  = double_constant< A0, 0x3ff965fea53d6e3dll> ();
      const A0 CBRT2I = double_constant< A0, 0x3fe965fea53d6e3dll> ();
      const A0 CBRT4I = double_constant< A0, 0x3fe428a2f98d728bll> ();
      typedef typename meta::as_integer<A0, signed>::type int_type;
      int_type e;
      A0 x = fast_frexp(z, e);
      x = horner < NT2_HORNER_COEFF_T(A0, 5,
                            (0xbfc13c93386fdff6ll,
                             0x3fe17e1fc7e59d58ll,
                             0xbfee8a4ca3ba37b8ll,
                             0x3ff23d6ee505873all,
                             0x3fd9c0c12122a4fell)
                            ) > (x);
      const bool flag = is_gez(e);
      int_type e1 =  nt2::abs(e);
      int_type rem = e1;
      e1 /= Three<int_type>();
      rem -= e1*Three<int_type>();
      e =  negate(e1, e);
      const A0 cbrt2 = flag ? CBRT2 : CBRT2I;
      const A0 cbrt4 = flag ? CBRT4 : CBRT4I;
      A0 fact = (rem == One<int_type>()) ? cbrt2: One<A0>();
      fact = (rem == Two<int_type>() ? cbrt4 : fact);
      x = fast_ldexp(x*fact, e);
      x -= (x-z/sqr(x))*Third<A0>();
      x -= (x-z/sqr(x))*Third<A0>(); //two newton passes
#ifndef BOOST_SIMD_NO_DENORMALS
      return b_or(x, bitofsign(a0))*f;
#else
      return b_or(x, bitofsign(a0));
#endif
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cbrt_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      A0 z =  nt2::abs(a0);
#ifndef BOOST_SIMD_NO_INFINITIES
      if (z == nt2::Inf<A0>() || (z == 0)) return a0;
#else
      if  (z == 0) return a0;
#endif
#ifndef BOOST_SIMD_NO_DENORMALS
      A0 f = One<A0>();
      if (z < Smallestposval<A0>())
      {
        z *= Twotonmb<A0>();
        f = Twotomnmbo_3<A0>();
      }
#endif
      const A0 CBRT2  = single_constant< A0, 0x3fa14518> ();
      const A0 CBRT4  = single_constant< A0, 0x3fcb2ff5> ();
      const A0 CBRT2I = single_constant< A0, 0x3f4b2ff5> ();
      const A0 CBRT4I = single_constant< A0, 0x3f214518> ();
      typedef typename meta::as_integer<A0, signed>::type int_type;
      int_type e;
      A0 x = fast_frexp(z, e);
      x = horner < NT2_HORNER_COEFF_T(A0, 5,
                                      (0xbe09e49a,
                                       0x3f0bf0fe,
                                       0xbf745265,
                                       0x3f91eb77,
                                       0x3ece0609)
                                     ) > (x);
      const bool flag = is_gez(e);
      int_type e1 =  nt2::abs(e);
      int_type rem = e1;
      e1 /= Three<int_type>();
      rem -= e1*Three<int_type>();
      e =  negate(e1, e);

      const A0 cbrt2 = flag ? CBRT2 : CBRT2I;
      const A0 cbrt4 = flag ? CBRT4 : CBRT4I;
      A0 fact = (rem ==  One<int_type>()) ? cbrt2 : One<A0>();
      fact = (rem == Two<int_type>()) ? cbrt4 : fact;
      x = fast_ldexp(x*fact, e);
      x -= (x-z/sqr(x))*Third<A0>();
#ifndef BOOST_SIMD_NO_DENORMALS
      return b_or(x, bitofsign(a0))*f;
#else
      return b_or(x, bitofsign(a0));
#endif
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SCALAR_J1_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SCALAR_J1_HPP_INCLUDED
#include <nt2/bessel/functions/j1.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/constants/digits.hpp>

#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/cos.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/is_less.hpp>
#include <nt2/include/functions/scalar/is_greater.hpp>
#include <nt2/include/functions/scalar/if_else.hpp>
#include <nt2/include/functions/scalar/splat.hpp>
#include <boost/simd/sdk/config.hpp>

#include <boost/simd/sdk/math.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::j1_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::j1(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::j1_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_ltz(a0)) return Nan<A0>();
#ifndef BOOST_SIMD_NO_INVALIDS
      if(nt2::is_inf(a0)) return Zero<A0>();
#endif
      if (is_eqz(a0)) return Zero<A0>();
    #if defined(BOOST_SIMD_HAS__J1)
      return ::_j1(a0);
    #elif defined(BOOST_SIMD_HAS_J1)
      return ::j1(a0);
    #else
      #error j1 not supported
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::j1_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_ltz(a0)) return Nan<A0>();
#ifndef BOOST_SIMD_NO_INVALIDS
      if(nt2::is_inf(a0)) return Zero<A0>();
#endif
      if (is_eqz(a0)) return Zero<A0>();
      A0 x = nt2::abs(a0);
      if (lt(x,Two<A0>()))
      {
        A0 z = sqr(x);
        return (z-single_constant<A0,0x416ae95a> ())*x*
          horner< NT2_HORNER_COEFF_T(A0, 5,
                             (0xb1a7a246,
                              0x35214df5,
                              0xb83e7a4f,
                              0x3afdefd1,
                              0xbd0b7da6
                              ) ) > (z);
        }
      A0 q = rec(x);
      A0 w = nt2::sqrt(q);
      A0 p3 = w *
        horner< NT2_HORNER_COEFF_T(A0, 8,
                           (0x3d8d98f9,
                            0xbe69f6b3,
                            0x3ea0ad85,
                            0xbe574699,
                            0x3bb21b25,
                            0x3e18ec50,
                            0x36a6f7c5,
                            0x3f4c4229
                            ) ) > (q);
          w = sqr(q);
          A0 xn =  q*
          horner< NT2_HORNER_COEFF_T(A0, 8,
                         (0xc233e16d,
                        0x424af04a,
                        0xc1c6dca7,
                        0x40e72299,
                        0xbfc5bd69,
                        0x3eb364d9,
                        0xbe27bad7,
                        0x3ebfffdd
                        ) ) > (w)-single_constant<A0,0x4016cbe4> ();
          return p3*nt2::cos(xn+x);
    }
  };
} }

#endif

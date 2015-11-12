//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SCALAR_Y0_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SCALAR_Y0_HPP_INCLUDED

#include <nt2/bessel/functions/y0.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/j0.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sin.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/simd/sdk/config.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y0_, tag::cpu_
                            , (A0)
                            , (scalar_< arithmetic_<A0> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::y0(result_type(a0));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y0_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      if (is_ltz(a0)) return Nan<result_type>();
#ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0)) return Nan<result_type>();
      if (is_inf(a0)) return Zero<result_type>();
#endif
      if (is_eqz(a0)) return Minf<result_type>();
#if defined(BOOST_SIMD_HAS__Y0)
      return ::_y0(a0);
#elif defined(BOOST_SIMD_HAS_Y0)
      return ::y0(a0);
#else
#error y0 not supported
#endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y0_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type stype;
      if (is_ltz(a0)) return Nan<result_type>();
#ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0)) return Nan<result_type>();
      if (is_inf(a0)) return Zero<result_type>();
#endif
      if (is_eqz(a0)) return Minf<result_type>();
      if (a0 <= Two<A0>())
      {
        A0 z = sqr(a0);
        A0 p2 = (z-single_constant<A0, 0x3edd4b3a>())*
          horner< NT2_HORNER_COEFF_T(stype, 5,
                                     (0x33cb0920,
                                      0xb71ded71,
                                      0x3a0c1a3e,
                                      0xbc81c8f4,
                                      0x3e2edb4f
                                       ) ) > (z);
        return p2+single_constant<A0, 0x3f22f983>()*nt2::log(a0)*nt2::j0(a0);
      }
      A0 q = rec(a0);
      A0 w = nt2::sqrt(q);
      A0 p3 = w *
        horner< NT2_HORNER_COEFF_T(stype, 8,
                                   (0xbd8c100e,
                                    0x3e3ef887,
                                    0xbe5ba616,
                                    0x3df54214,
                                    0xbb69539e,
                                    0xbd4b8bc1,
                                    0xb6612dc2,
                                    0x3f4c422a
                                     ) ) > (q);
       w = sqr(q);
       A0 xn =  q*
         horner< NT2_HORNER_COEFF_T(stype, 8,
                                    (0x4201aee0,
                                     0xc2113945,
                                     0x418c7f6a,
                                     0xc09f3306,
                                     0x3f8040aa,
                                     0xbe46a57f,
                                     0x3d84ed6e,
                                     0xbdffff97
                                      ) ) > (w)-Pio_4<A0>();
      return p3*nt2::sin(xn+a0);
    }
  };
} }

#endif

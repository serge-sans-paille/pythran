//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_FMA_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_FMA_HPP_INCLUDED

#include <nt2/arithmetic/functions/fma.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/is_real.hpp>
#include <nt2/include/functions/is_imag.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/seladd.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/sdk/complex/meta/as_complex.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <boost/simd/sdk/config.hpp>

// for optimize
#include <nt2/include/functions/fnma.hpp>

namespace nt2 { namespace ext
{


  //0 ccc
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(-nt2::imag(a1), nt2::imag(a0), fma(nt2::real(a0), nt2::real(a1), nt2::real(a2)));
      r_type i = fma(nt2::real(a1), nt2::imag(a0), fma(nt2::real(a0), nt2::imag(a1), nt2::imag(a2)));
      return checkr(a0, a1, a2, result_type(r, i));
    }

    static inline result_type checkr(const A0& a0,  const A1& a1,  const A2& a2, const result_type& res)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return res;
#else
      if(nt2::any(is_invalid(res)))
      {
        result_type z = nt2::multiplies(a0, a1);
        z+=a2;
        return if_else(is_invalid(res), z, res);
      }
      return res;
#endif

    }
  };


  //8 acc
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0> > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A1 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(a0, real(a1), real(a2));
      r_type i = fma(a0, imag(a1), imag(a2));
      return checkr(a0, a1, a2, r, i);
    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, r_type& r, r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      r =  if_else(is_invalid(a0),
                   if_else(is_real(a1),
                           r,
                           if_else(nt2::is_imag(a1), real(a2),r)),
                   r
        );
      i =  if_else(is_invalid(a0),
                   if_else(is_real(a1), imag(a2), i),
                   i);
      return result_type(r, i);
#endif
    }
  };

  //9 cac
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<arithmetic_<A1> > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  //10 cca
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_<arithmetic_<A2> > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r =fma(-nt2::imag(a1), nt2::imag(a0), fma(nt2::real(a1), nt2::real(a0), a2));
      r_type i = fma(nt2::real(a1), nt2::imag(a0), nt2::real(a0)*nt2::imag(a1));
      return checkr(a0, a1, a2, r, i);

    }
    static inline result_type checkr(const A0& a0, const A1& a1, const A2& a2, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(nt2::logical_and(nt2::is_real(a1), nt2::is_real(a0)), nt2::is_nez(i)));
      BOOST_AUTO_TPL(testr, nt2::logical_and(logical_or(nt2::is_eqz(a1), is_eqz(a0)),
                                             logical_and(logical_and(is_imag(a0),
                                                                     is_imag(a1)),
                                                         nt2::is_invalid(r))));
      return result_type(if_else(testr, a2, r), nt2::if_zero_else(test, i));
#endif

    }
  };

  //11 caa
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<complex_<arithmetic_<A0> > > )
                              (generic_< arithmetic_<A1>  > )
                              (generic_< arithmetic_<A2>  > )
    )
  {
    typedef A0 result_type;
    typedef typename meta::as_real<A0>::type r_type;
    NT2_FUNCTOR_CALL(3)
    {
      r_type r = fma(nt2::real(a0), a1, a2);
      r_type i = nt2::imag(a0)*a1;
      return checkr(a0, r, i);
    }
    static inline result_type checkr(const A0& a0, const r_type& r, const r_type& i)
    {
#ifdef BOOST_SIMD_NO_INVALIDS
      return result_type(r, i);
#else
      BOOST_AUTO_TPL(test, nt2::logical_and(nt2::is_real(a0), nt2::is_nez(i)));
      return result_type(r, nt2::if_zero_else(test, i));
#endif
    }
  };

  //12 aca
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_< arithmetic_<A0>  > )
                              (generic_<complex_<arithmetic_<A1> > > )
                              (generic_< arithmetic_<A2>  > )
    )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return fma(a1, a0, a2);
    }
  };

  //13 aac
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fma_, tag::cpu_, (A0)(A1)(A2)
                              , (generic_<arithmetic_<A0>  > )
                              (generic_<arithmetic_<A1>  > )
                              (generic_<complex_<arithmetic_<A2> > > )
    )
  {
    typedef A2 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      return result_type( fma(a0, a1, nt2::real(a2))
                          , nt2::imag(a2)
        );
    }
  };

 } }

#endif

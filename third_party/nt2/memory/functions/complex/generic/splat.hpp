//==============================================================================
//        Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//        Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//         Distributed under the Boost Software License, Version 1.0.
//                See accompanying file LICENSE.txt or copy at
//                    http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_MEMORY_FUNCTIONS_COMPLEX_GENERIC_SPLAT_HPP_INCLUDED
#define NT2_MEMORY_FUNCTIONS_COMPLEX_GENERIC_SPLAT_HPP_INCLUDED

#include <nt2/memory/functions/splat.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/bitwise_cast.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::splat_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< unspecified_<A0> >)
                              ((target_<simd_<complex_<arithmetic_<A1> >, X > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&) const
    {
      typedef typename meta::as_real<result_type>::type rtype;
      return result_type(splat < rtype>(nt2::real(a0)),  splat<rtype>(nt2::imag(a0)));
    }
  };

   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::splat_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< unspecified_<A0> >)
                              ((target_<simd_<dry_< arithmetic_<A1> >, X > >))
                            )
  {
    typedef typename A1::type result_type;
    inline result_type operator()(const A0& a0, const A1&) const
    {
      typedef typename meta::as_real<result_type>::type rtype;
      return bitwise_cast<result_type>(splat<rtype>(nt2::real(a0)));
    }
  };
} }

#endif

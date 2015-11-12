//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_GENERIC_DGAMMAINC_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_GENERIC_DGAMMAINC_HPP_INCLUDED

#include <nt2/euler/functions/dgammainc.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_nan.hpp>
#include <nt2/include/functions/simd/gammaln.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dgammainc_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< arithmetic_<A0> >)
                              (generic_< arithmetic_<A1> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0, A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::dgammainc(nt2::tofloat(a0), nt2::tofloat(a1));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dgammainc_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& x, const A1& a) const
    {
      result_type tmp =  nt2::if_zero_else(nt2::is_equal(x, nt2::One<A0>()),
                                           nt2::minusone(a)*nt2::log(x)
                                          );
      if (nt2::is_eqz(a)) return Nan<result_type>(); ;
      return nt2::exp(tmp-x-nt2::gammaln(a));
    }
  };
} }

#endif

//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_DOT_HPP_INCLUDED
#define NT2_REDUCTION_FUNCTIONS_COMPLEX_GENERIC_DOT_HPP_INCLUDED

#include <nt2/reduction/functions/dot.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/constants/false.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/conj.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_, (A0),
                              ((generic_ < complex_< arithmetic_ <A0> > > ))
                              ((generic_ < complex_< arithmetic_ <A0> > > ))
    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2:: sum(nt2::multiplies(a0, conj(a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_, (A0),
                              ((generic_ < dry_< arithmetic_ <A0> > > ))
                              ((generic_ < dry_< arithmetic_ <A0> > > ))
    )
  {
    typedef typename meta::scalar_of<A0>::type  result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(nt2::sum(nt2::real(a0)*nt2::real(a1)));
    }
  };



  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_, (A0)(A1),
                              ((generic_ < complex_< arithmetic_ <A0> > > ))
                              ((generic_ < complex_< arithmetic_ <A0> > > ))
                              ((scalar_<integer_<A1> > ))
    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;
    BOOST_FORCEINLINE
      result_type operator()(const A0& a0,const A0& a1, const A1& ) const
    {
      return dot(a0, a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dot_, tag::cpu_, (A0)(A1),
                              ((generic_ < dry_< arithmetic_ <A0> > > ))
                              ((generic_ < dry_< arithmetic_ <A0> > > ))
                              ((scalar_<integer_<A1> > ))
    )
  {
    typedef typename meta::scalar_of<A0>::type  result_type;
    BOOST_FORCEINLINE
      result_type operator()(const A0& a0,const A0& a1, const A1& ) const
    {
      return dot(a0, a1);
    }
  };

} }

#endif

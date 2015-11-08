//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Hypotributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_HYPOT_HPP_INCLUDED
#define NT2_ARITHMETIC_FUNCTIONS_COMPLEX_GENERIC_HYPOT_HPP_INCLUDED
#include <nt2/arithmetic/functions/hypot.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hypot_, tag::cpu_, (A0)(A1)
                            , (generic_< complex_ < arithmetic_<A0> > > )
                              (generic_< complex_ < arithmetic_<A1> > > )
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::hypot(nt2::abs(a0), nt2::abs(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hypot_, tag::cpu_, (A0)(A1)
                            , (generic_< dry_ < arithmetic_<A0> > > )
                              (generic_< dry_ < arithmetic_<A1> > > )
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::hypot(nt2::real(a0), nt2::real(a1)) ;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hypot_, tag::cpu_, (A0)(A1)
                            ,  (generic_< arithmetic_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)

                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::hypot(a0, nt2::abs(a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hypot_, tag::cpu_, (A0)(A1)
                            ,  (generic_< dry_ < arithmetic_<A0> > >)
                               (generic_< complex_< arithmetic_<A1> > >)

                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return  nt2::hypot(a1, a0);
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hypot_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< arithmetic_<A1> >)

                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return  nt2::hypot(a1, a0);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hypot_, tag::cpu_, (A0)(A1)
                            ,  (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< dry_ < arithmetic_<A1> > >)

                            )
  {
    typedef typename meta::as_real<A0>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return  nt2::hypot(a1, a0);
    }
  };
} }

#endif

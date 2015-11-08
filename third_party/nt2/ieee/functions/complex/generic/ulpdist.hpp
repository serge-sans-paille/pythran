//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_ULPDIST_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_ULPDIST_HPP_INCLUDED

#include <nt2/ieee/functions/ulpdist.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <nt2/sdk/complex/meta/as_real.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ulpdist_, tag::cpu_
                            , (A0)
                            , (generic_< complex_< floating_<A0> > >)
                              (generic_< complex_< floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::max ( nt2::ulpdist(nt2::real(a0), nt2::real(a1))
                      , nt2::ulpdist(nt2::imag(a0), nt2::imag(a1))
                      );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ulpdist_, tag::cpu_, (A0)
                            , (generic_< dry_< floating_<A0> > >)
                              (generic_< dry_< floating_<A0> > >)
                            )
  {
    typedef typename meta::as_real<A0>::type result_type;

    BOOST_FORCEINLINE NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::ulpdist(nt2::real(a0), nt2::real(a1));
    }
  };
} }

#endif

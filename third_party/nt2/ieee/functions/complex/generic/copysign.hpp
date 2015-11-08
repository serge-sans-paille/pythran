//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_COPYSIGN_HPP_INCLUDED
#define NT2_IEEE_FUNCTIONS_COMPLEX_GENERIC_COPYSIGN_HPP_INCLUDED

#include <nt2/ieee/functions/copysign.hpp>
#include <nt2/include/functions/copysign.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/real.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
                             (A0),
                             ((generic_<complex_ < floating_<A0> > >))
                             ((generic_<complex_ < floating_<A0> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return nt2::multiplies(abs(a0), sign(a1));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
                             (A0),
                             ((generic_<dry_ < floating_<A0> > >))
                             ((generic_<dry_ < floating_<A0> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      return result_type(copysign(nt2::real(a0), nt2::real(a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
                             (A0)(A1),
                             ((generic_<complex_ < floating_<A0> > >))
                             ((generic_<scalar_ < floating_<A1> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A1 m = abs(a0);
      return result_type(copysign(m, a1));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
                             (A0)(A1),
                             ((generic_<scalar_ < floating_<A0> > >))
                             ((generic_<complex_ < floating_<A1> > >))
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A1 m = abs(a0);
      return m*sign(a1);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
                             (A0)(A1),
                             ((generic_<complex_ < floating_<A0> > >))
                             ((generic_<dry_ < floating_<A1> > >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      A1 m = abs(a0);
      return result_type(copysign(m, real(a1)));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::copysign_, tag::cpu_,
                             (A0)(A1),
                             ((generic_<dry_ < floating_<A0> > >))
                             ((generic_<complex_ < floating_<A1> > >))
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      A1 m = abs(a0);
      return m*sign(a1);
    }
  };

} }
#endif

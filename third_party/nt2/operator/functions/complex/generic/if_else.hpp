//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_IF_ELSE_HPP_INCLUDED
#define NT2_OPERATOR_FUNCTIONS_COMPLEX_GENERIC_IF_ELSE_HPP_INCLUDED

#include <nt2/operator/functions/if_else.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/include/functions/real.hpp>
#include <nt2/include/functions/imag.hpp>
#include <boost/dispatch/attributes.hpp>

namespace nt2 { namespace ext
{
  //complex/complex 1 -1
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)
                             , (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< complex_< arithmetic_<A0> > >)
                               (generic_< complex_< arithmetic_<A0> > >)
                             )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A0& a1, const A0&a2) const
    {
      return result_type(if_else(is_nez(a0), nt2::real(a1), nt2::real(a2)),
                         if_else(is_nez(a0), nt2::imag(a1), nt2::imag(a2)));
    }
  };

  //complex/complex 1 -1
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                             , (generic_< logical_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                               (generic_< complex_< arithmetic_<A1> > >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return result_type(if_else(a0, nt2::real(a1), nt2::real(a2)),
                         if_else(a0, nt2::imag(a1), nt2::imag(a2)));
    }
  };

  //complex/complex 2
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                             , (generic_< fundamental_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                               (generic_< complex_< arithmetic_<A1> > >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return if_else( is_nez(a0), a1, a2 );
    }
  };


  //dry/dry 1 -5
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                             , (generic_< logical_<A0> >)
                               (generic_< dry_< arithmetic_<A1> > >)
                               (generic_< dry_< arithmetic_<A1> > >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return result_type(if_else(a0, nt2::real(a1), nt2::real(a2)));
    }
  };

  //dry/dry 2
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)
                             , (generic_< fundamental_<A0> >)
                               (generic_< dry_< arithmetic_<A1> > >)
                               (generic_< dry_< arithmetic_<A1> > >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A1&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //dry/complex 1 -6
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< logical_<A0> >)
                               (generic_< dry_< arithmetic_<A1> > >)
                               (generic_< complex_< arithmetic_<A2> > >)
                             )
  {
    typedef A2 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, result_type(nt2::real(a1)), a2);
    }
  };

  //dry/complex 2
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< fundamental_<A0> >)
                               (generic_< dry_< arithmetic_<A1> > >)
                               (generic_< complex_< arithmetic_<A2> > >)
                             )
  {
    typedef A2 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //complex/dry/ 1 -7
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< logical_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                               (generic_< dry_< arithmetic_<A2> > >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, a1, result_type(nt2::real(a2)));
    }
  };

  //complex/dry/ 2
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< fundamental_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                               (generic_< dry_< arithmetic_<A2> > >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //arithmetic/dry 1
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< logical_<A0> >)
                               (generic_< arithmetic_<A1> >)
                               (generic_< dry_< arithmetic_<A2> > >)
                             )
  {
    typedef A2 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return result_type(if_else(a0, a1, nt2::real(a2)));
    }
  };

  //arithmetic/dry 2
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< fundamental_<A0> >)
                               (generic_< arithmetic_<A1> >)
                               (generic_< dry_< arithmetic_<A2> > >)
                             )
  {
    typedef A2 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //arithmetic/complex 1
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< logical_<A0> >)
                               (generic_< arithmetic_<A1> >)
                               (generic_< complex_< arithmetic_<A2> > >)
                             )
  {
    typedef A2 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(a0, result_type(a1), a2);
    }
  };

  //arithmetic/complex 2
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< fundamental_<A0> >)
                               (generic_< arithmetic_<A1> >)
                               (generic_< complex_< arithmetic_<A2> > >)
                             )
  {
    typedef A2 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //dry/arithmetic/   1
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< logical_<A0> >)
                               (generic_< dry_< arithmetic_<A1> > >)
                               (generic_< arithmetic_<A2> >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return result_type(if_else(a0, nt2::real(a1), a2));
    }
  };

  //dry/arithmetic_ 2
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< fundamental_<A0> >)
                               (generic_< dry_< arithmetic_<A1> > >)
                               (generic_< arithmetic_<A2> >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

  //complex/arithmetic/   1
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< logical_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                               (generic_< arithmetic_<A2> >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return result_type(if_else(a0, a1, result_type(a2)));
    }
  };

  //complex/arithmetic_ 2
  NT2_FUNCTOR_IMPLEMENTATION ( nt2::tag::if_else_, tag::cpu_, (A0)(A1)(A2)
                             , (generic_< fundamental_<A0> >)
                               (generic_< complex_< arithmetic_<A1> > >)
                               (generic_< arithmetic_<A2> >)
                             )
  {
    typedef A1 result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1& a1, const A2&a2) const
    {
      return if_else(is_nez(a0), a1, a2);
    }
  };

} }

#endif

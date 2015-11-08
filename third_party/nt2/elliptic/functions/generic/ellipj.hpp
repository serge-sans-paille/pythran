//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_GENERIC_ELLIPJ_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_GENERIC_ELLIPJ_HPP_INCLUDED

#include <nt2/elliptic/functions/ellipj.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/simd/am.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/sincos.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellipj_, tag::cpu_,
                             (A0)(A1),
                             (generic_<unspecified_<A0> >)
                             (generic_<floating_<A1> >)

                            )
  {
    typedef boost::fusion::tuple<A0,A0,A0>        result_type;

    inline result_type operator()(A0 const& a0,A1 const & a1) const
    {
      typedef typename nt2::meta::scalar_of<A0>::type sA0;
      A0 s, c, d;
      nt2::ellipj(a0, a1, nt2::Eps<sA0>(), s, c, d);
      return result_type(s, c, d);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellipj_, tag::cpu_,
                             (A0)(A1)(A2),
                             (generic_<unspecified_<A0> >)
                             (generic_<floating_<A1> >)
                             (scalar_<floating_<A2> >)

                            )
  {
    typedef boost::fusion::tuple<A0,A0,A0>        result_type;

    inline result_type operator()(A0 const& a0,A1 const & a1,A2 const & a2) const
    {
      A0 s, c, d;
      nt2::ellipj(a0, a1, a2, s, c, d);
      return result_type(s, c, d);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipj_, tag::cpu_,
                               (A0)(A1)(A2),
                               (generic_<unspecified_<A0> >)
                               (generic_<floating_<A1> >)
                               (scalar_<floating_<A2> >)
                               (generic_<unspecified_<A0> >)
                            )
  {
    typedef boost::fusion::tuple<A0,A0>        result_type;

    inline result_type operator()(A0 const& a0,A1 const & a1,A2 const & a2,A0 & a3) const
    {
      A0 s, c;
      nt2::ellipj(a0,a1,a2,s,c,a3);
      return result_type(s, c);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipj_, tag::cpu_,
                               (A0)(A1)(A2),
                               (generic_<unspecified_<A0> >)
                               (generic_<floating_<A1> >)
                               (unspecified_<A2>)               //passing _()
                               (generic_<unspecified_<A0> >)
                            )
  {
    typedef boost::fusion::tuple<A0,A0>        result_type;

    inline result_type operator()(A0 const& a0,A1 const & a1,A2 const &,A0 & a3) const
    {
      typedef typename nt2::meta::scalar_of<A0>::type sA0;
      A0 s, c;
      nt2::ellipj(a0,a1,Eps<sA0>(),s,c,a3);
      return result_type(s, c);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipj_, tag::cpu_,
                               (A0)(A1)(A2),
                               (generic_<unspecified_<A0> >)
                               (generic_<floating_<A1> >)
                               (scalar_<floating_<A2> >)
                               (generic_<unspecified_<A0> >)
                               (generic_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(A0 const& a0,A1 const & a1,A2 const & a2,A0 & a3,A0 & a4) const
    {
      A0 s;
      nt2::ellipj(a0,a1,a2,s,a3,a4);
      return s;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipj_, tag::cpu_,
                               (A0)(A1)(A2),
                               (generic_<unspecified_<A0> >)
                               (generic_<floating_<A1> >)
                               (unspecified_<A2>)         //passing _()
                               (generic_<unspecified_<A0> >)
                               (generic_<unspecified_<A0> >)
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(A0 const& a0,A1 const & a1,A2 const &,A0 & a3,A0 & a4) const
    {
      typedef typename nt2::meta::scalar_of<A0>::type sA0;
      A0 s;
      nt2::ellipj(a0,a1,Eps<sA0>(),s,a3,a4);
      return s;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipj_, tag::cpu_,
                               (A0)(A1)(A2),
                               (generic_<floating_<A0> >)
                               (generic_<floating_<A1> >)
                               (scalar_<floating_<A2> >)
                               (generic_<floating_<A0> >)
                               (generic_<floating_<A0> >)
                               (generic_<floating_<A0> >)
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0, A1 const & a1, A2 const & a2,
                                  A0 & a3, A0 & a4, A0 & a5) const
    {
      A0 a = am(a0, a1, a2, 'm');
      a3 = nt2::sincos(a, a4);
      a5 = nt2::sqrt(oneminus(if_zero_else(is_eqz(a1), a1*nt2::sqr(a3))));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipj_, tag::cpu_,
                               (A0)(A1)(A2),
                               (generic_<floating_<A0> >)
                               (generic_<floating_<A1> >)
                               (unspecified_<A2>)       //passing _()
                               (generic_<floating_<A0> >)
                               (generic_<floating_<A0> >)
                               (generic_<floating_<A0> >)
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0, A1 const & a1, A2 const &,
                                  A0 & a3, A0 & a4, A0 & a5) const
    {
      typedef typename nt2::meta::scalar_of<A0>::type sA0;
      A0 a = am(a0, a1, Eps<sA0>(), 'm');
      a3 = nt2::sincos(a, a4);
      a5 = nt2::sqrt(oneminus(if_zero_else(is_eqz(a1), a1*nt2::sqr(a3))));
    }
  };

} }
#endif

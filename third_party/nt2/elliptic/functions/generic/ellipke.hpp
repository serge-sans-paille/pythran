//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_GENERIC_ELLIPKE_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_GENERIC_ELLIPKE_HPP_INCLUDED

#include <nt2/elliptic/functions/ellipke.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellipke_, tag::cpu_,
                             (A0),
                             (generic_<floating_<A0> >)

                            )
  {
    typedef std::pair<A0, A0> result_type;

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename nt2::meta::scalar_of<A0>::type sA0;
      A0 first, second;
      nt2::ellipke(a0, nt2::Eps<sA0>(), first, second);
      return result_type(first, second);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::ellipke_, tag::cpu_,
                             (A0)(A1),
                             (generic_<floating_<A0> >)
                             (scalar_<floating_<A1> >)

                            )
  {
    typedef std::pair<A0, A0> result_type;

    NT2_FUNCTOR_CALL(2)
    {
      A0 first, second;
      nt2::ellipke(a0, a1, first, second);
      return result_type(first, second);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipke_, tag::cpu_,
                               (A0)(A1),
                               (generic_<floating_<A0> >)
                               (scalar_<floating_<A1> >)
                               (generic_<floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    inline result_type operator()(A0 const& a0,A1 const & a1,A0 & a3) const
    {
      A0 a2;
      nt2::ellipke(a0,a1,a2,a3);
      return a2;
    }
  };

} }
#endif

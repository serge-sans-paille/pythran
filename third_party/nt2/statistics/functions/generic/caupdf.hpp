//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_CAUPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_CAUPDF_HPP_INCLUDED
#include <nt2/statistics/functions/caupdf.hpp>
#include <nt2/include/functions/atanpi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/constants/invpi.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/globalall.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caupdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1) { return nt2::rec(nt2::oneplus(nt2::sqr(a0)))*Invpi<A0>(); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caupdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                             )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2) { return nt2::caupdf(a0-a1); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::caupdf_, tag::cpu_
                            , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                               (generic_< floating_<A1> >)
                               (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
      {
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "scale parameter must be positive");
        return (a2*Invpi<A0>())/(nt2::sqr(a2)+nt2::sqr(a0-a1));
      }
  };

} }

#endif

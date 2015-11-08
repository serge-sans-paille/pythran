//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_NORMPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_NORMPDF_HPP_INCLUDED
#include <nt2/statistics/functions/normpdf.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/atanpi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/constants/mhalf.hpp>
#include <nt2/include/constants/invsqrt_2pi.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::exp(Mhalf<A0>()*nt2::sqr(a0))*Invsqrt_2pi<A0>();
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        return nt2::exp(Mhalf<A0>()*nt2::sqr(a0-a1))*Invsqrt_2pi<A0>();
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normpdf_, tag::cpu_
                            , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(a2)), "sigma(s) must be positive");
      return nt2::exp(Mhalf<A0>()*nt2::sqr((a0-a1)/a2))*Invsqrt_2pi<A0>();
    }
  };


} }

#endif

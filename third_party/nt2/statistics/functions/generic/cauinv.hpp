//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_CAUINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_CAUINV_HPP_INCLUDED
#include <nt2/statistics/functions/cauinv.hpp>
#include <nt2/include/functions/proper_tanpi.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/globalall.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        return nt2::proper_tanpi(a0-Half<A0>());
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)
                              , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2) {
      return nt2::cauinv(a0)+a1;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::cauinv_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3) {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a2)), "scale parameter must be positive");
      return nt2::fma(nt2::cauinv(a0), a2, a1);
    }
  };

} }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_EXPPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_EXPPDF_HPP_INCLUDED
#include <nt2/statistics/functions/exppdf.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/uminus.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exppdf_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        return nt2::if_zero_else(nt2::is_ltz(a0), nt2::exp(-a0));
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::exppdf_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "mu parameter must be positive");
        return nt2::if_zero_else(nt2::is_ltz(a0), a1*nt2::exp(-a0*a1));
      }
  };

} }

#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_UNIFPDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_UNIFPDF_HPP_INCLUDED

#include <nt2/statistics/functions/unifpdf.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/logical_andnot.hpp>
#include <nt2/include/functions/logical_or.hpp>
#include <nt2/include/functions/is_negative.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return if_else(is_nan(a0), a0,if_else_zero(logical_andnot(le(a0, One<A0>()), is_negative(a0)), One<A0>()));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifpdf_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      A0 z = a2-a1;
      return nt2::if_allbits_else(logical_or(is_lez(z), is_nan(a0)),
                                  nt2::if_zero_else(logical_or(lt(a0,a1),gt(a0,a2)),
                                                    nt2::rec(z)
                                                    )
                                  );
    }
  };
} }

#endif

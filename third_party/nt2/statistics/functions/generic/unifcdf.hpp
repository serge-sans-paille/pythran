//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_UNIFCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_UNIFCDF_HPP_INCLUDED
#include <nt2/statistics/functions/unifcdf.hpp>

#include <nt2/include/functions/is_not_greater.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/divides.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/is_lez.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
      {
        A0 o = One<A0>();
        return nt2::if_zero_else( nt2::is_ltz(a0),
                                  nt2::if_else(is_not_greater(a0,o), a0, o)
                                 );
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifcdf_, tag::cpu_
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

      return nt2::if_allbits_else ( is_lez(z)
                                  , nt2::if_zero_else
                                    ( lt(a0,a1)
                                    , nt2::if_else( is_not_greater(a0,a2)
                                                  , (a0-a1)/z
                                                  , One<A0>()
                                                  )
                                    )
                                  );
    }
  };
} }

#endif

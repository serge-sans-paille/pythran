//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_UNIFINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_UNIFINV_HPP_INCLUDED
#include <nt2/statistics/functions/unifinv.hpp>

#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/logical_and.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_gez.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/nan.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return if_else( logical_and(is_gez(a0), le(a0, One<A0>()))
                    , a0
                    , Nan<A0> ()
                    );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::unifinv_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG( nt2::all( gt(a2,a1) )
                      , "b(s) must be strictly greater than a(s)"
                      );

      return fma( a0
                , if_allbits_else ( logical_or(gt(a0, a2), lt(a0, a1))
                                  , a2-a1
                                  )
                , a1
                );
    }
  };
} }
#endif

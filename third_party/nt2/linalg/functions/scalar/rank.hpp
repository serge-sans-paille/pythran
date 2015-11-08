//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_SCALAR_RANK_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_SCALAR_RANK_HPP_INCLUDED
#include <nt2/linalg/functions/rank.hpp>
#include <nt2/include/functions/scalar/rank.hpp>
#include <nt2/include/functions/inbtrue.hpp>
#include <nt2/include/functions/gt.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/svd.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2{ namespace ext
{
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rank_, tag::cpu_,
                                (A0)
                                ,((ast_<A0, nt2::container::domain>))
                                )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef size_t result_type;
    typedef nt2::container::table<rtype_t>  base_type;

    NT2_FUNCTOR_CALL(1)
    {
      base_type s = svd(a0);
      return size_t(inbtrue(gt(s,  nt2::length(a0)*nt2::eps(s(1)))));
    }
  };
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rank_, tag::cpu_,
                                (A0)(A1)
                                ,((ast_<A0, nt2::container::domain>))
                                (scalar_<floating_<A1 > >)
                                )
  {
    typedef typename A0::value_type type_t;
    typedef typename meta::as_real<type_t>::type rtype_t;
    typedef size_t result_type;
    typedef nt2::container::table<rtype_t>  base_type;

    NT2_FUNCTOR_CALL(2)
    {
      base_type s = svd(a0);
      rtype_t epsi =  (a1 < 0) ?  nt2::length(a0)*nt2::eps(s(1)): a1;
      return  size_t(inbtrue(gt(s, epsi)));
    }
  };

} }


#endif

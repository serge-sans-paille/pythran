//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_REDUCE_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_REDUCE_HPP_INCLUDED

#include <nt2/polynom/functions/reduce.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reduce_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {

    typedef typename A0::value_type value_type;
    typedef typename nt2::meta::call<nt2::tag::colon_(size_t, size_t)>::type                     T1;
    typedef typename nt2::meta::call<nt2::tag::function_(const typename A0::nt2_expression&, size_t, T1)>::type  result_type;
    NT2_FUNCTOR_CALL(1)
    {
      size_t na0 =  nt2::numel(a0);
      size_t idx = na0+1;
      for(size_t i=1; i <= na0 ; ++i)
      {
        if (nt2::is_nez(a0(i))) {idx = i; break;}
      }

      return a0(nt2::One<size_t>(), _(idx,na0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reduce_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<floating_<A1> > )
                            )
  {

    typedef typename A0::value_type value_type;
    typedef typename nt2::meta::call<nt2::tag::colon_(size_t, size_t)>::type                     T1;
    typedef typename nt2::meta::call<nt2::tag::function_(const typename A0::nt2_expression&, size_t, T1)>::type  result_type;
    NT2_FUNCTOR_CALL(2)
    {
      size_t na0 =  nt2::numel(a0);
      size_t idx = na0+1;
      A1 thresh = a1*nt2::globalmax(nt2::abs(a0));
      for(size_t i=1; i <= na0 ; ++i)
      {
        if (nt2::gt(nt2::abs(a0(i)), thresh)) {idx = i; break;}
      }

      return a0(nt2::One<size_t>(), _(idx,na0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reduce_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (unspecified_<A1>  )
                            )
  {

    typedef typename A0::value_type value_type;
    typedef typename nt2::meta::call<nt2::tag::colon_(size_t, size_t)>::type                     T1;
    typedef typename nt2::meta::call<nt2::tag::function_(const typename A0::nt2_expression&, size_t, T1)>::type  result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      size_t na0 =  nt2::numel(a0);
      size_t idx = na0+1;
      for(size_t i=1; i <= na0 ; ++i)
      {
        if (nt2::is_eqz(a0(i))) continue;
        if (globalall(nt2::is_finite(a0(nt2::_(i+1, end_))/a0(i)))) {idx = i; break;}
      }
      return a0(nt2::One<size_t>(), nt2::_(idx,na0));
    }
  };

} }


#endif

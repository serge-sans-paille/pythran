//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_COMMON_NELDERMEAD_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_COMMON_NELDERMEAD_HPP_INCLUDED

#include <nt2/optimization/functions/neldermead.hpp>
#include <nt2/include/constants/true.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/ones.hpp>

#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/last_index.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/constants/oneo_10.hpp>
#include <nt2/optimization/output.hpp>
#include <nt2/optimization/options.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/optimization/functions/details/nelder_impl.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::neldermead_, tag::cpu_
                              , (F)(A)(H)(O)
                            , (unspecified_< F >)
                              ((ast_< A, nt2::container::domain>))
                              ((ast_< H, nt2::container::domain>))
                              (unspecified_<O>)
    )
  {
    typedef typename A::value_type                                  value_type;
    typedef typename meta::as_real<value_type>::type                 real_type;
    typedef typename meta::as_logical<value_type>::type                 l_type;
    typedef nt2::container::table<value_type>                            tab_t;
    typedef nt2::container::table<real_type>                            rtab_t;
    typedef nt2::container::table<ptrdiff_t>                            ltab_t;
    typedef optimization::output<tab_t,real_type>       result_type;

    result_type operator()(F crit, A const& init, H const& w, O const& o)
    {
      details::nelder_impl<tab_t> nelder;
      tab_t a = init;
      nelder.optimize(crit, a, w, o);
//      BOOST_ASSERT_MSG(nelder.convok(), "neldermead was not convergent");
      // We didn't converged -- add message for this
      result_type that = {a,nelder.lasteval(),nelder.nbiteration(),nelder.convok(), tab_t()};
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::neldermead_, tag::cpu_
                              , (F)(A)(H)(O)
                            , (unspecified_< F >)
                              ((ast_< A, nt2::container::domain>))
                              (scalar_ < unspecified_ < H > > )
                              (unspecified_<O>)
                            )
  {
    typedef typename nt2::meta::call < nt2::tag::repnum_(size_t, size_t) > ::type T0;
    typedef typename nt2::meta::call < nt2::tag::neldermead_(F, A const &, T0, O const&)>::type result_type;
    result_type operator()(F f, A const& init, H const& step, O const& o)
    {
      typedef typename A::value_type                                  value_type;
      return neldermead(f, init, nt2::repnum(value_type(step), size_t(1), nt2::numel(init)), o);
    }
  };
} }
#endif

//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_COMMON_ROSENBROCK_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_COMMON_ROSENBROCK_HPP_INCLUDED

#include <nt2/optimization/functions/rosenbrock.hpp>
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
#include <nt2/optimization/functions/details/ros_impl.hpp>


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::rosenbrock_, tag::cpu_
                              , (F)(A)(O)
                            , (unspecified_< F >)
                              ((ast_< A, nt2::container::domain>))
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

    result_type operator()(F crit, A const& init, O const& o)
    {
      details::ros_impl<tab_t> ros;
      tab_t a = init;
      ltab_t w = nt2::ones(a.extent(), meta::as_<ptrdiff_t>()); //which;
      ros.optimize(crit, a, o);
      BOOST_ASSERT_MSG(ros.convok(), "rosenbrock was not convergent");
      // We didn't converged -- add message for this
      result_type that = {a,ros.lasteval(),ros.nbiteration(),ros.convok(),tab_t()};
      return that;
    }
  };

} }
#endif

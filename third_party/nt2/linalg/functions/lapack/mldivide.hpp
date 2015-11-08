//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_LAPACK_MLDIVIDE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_LAPACK_MLDIVIDE_HPP_INCLUDED

#include <nt2/linalg/functions/mldivide.hpp>
#include <nt2/linalg/functions/details/eval_mldivide.hpp>
#include <nt2/include/functions/linsolve.hpp>

#include <nt2/dsl/functions/terminal.hpp>
#include <nt2/core/container/table/kind.hpp>
#include <nt2/linalg/details/utility/f77_wrapper.hpp>

#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mldivide_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((expr_ < container_< nt2::tag::table_, double_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < container_< nt2::tag::table_, double_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef nt2::table<double> result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {

        result_type entry(a0);
        result_type that;

        nt2_la_int  m   = nt2::height(a0);
        nt2_la_int  n   = nt2::width(a0);
        nt2::table<nt2_la_int> piv;

        if (eval_param(a0,a1,that)) return that;

        that = nt2::linsolve(entry,that);


        return that;
     }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::mldivide_, tag::cpu_
                            , (A0)(S0)(A1)(S1)
                            , ((expr_ < container_< nt2::tag::table_, single_<A0>, S0 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                              ((expr_ < container_< nt2::tag::table_, single_<A1>, S1 >
                                      , nt2::tag::terminal_
                                      , boost::mpl::long_<0>
                                      >
                              ))
                            )
  {
     typedef  nt2::table<float> result_type;

     BOOST_FORCEINLINE result_type operator()(A0& a0, A1& a1) const
     {
        result_type entry(a0);
        result_type that;

        nt2_la_int  m   = nt2::height(a0);
        nt2_la_int  n   = nt2::width(a0);

        nt2::table<nt2_la_int> piv;

        if (eval_param(a0,a1,that)) return that;

        that = nt2::linsolve(entry,that);


        return that;
     }
  };

} }

#endif

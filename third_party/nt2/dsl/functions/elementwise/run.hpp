//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_ELEMENTWISE_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_ELEMENTWISE_RUN_HPP_INCLUDED

#include <nt2/dsl/functions/run.hpp>
#include <nt2/include/functions/transform.hpp>
#include <nt2/sdk/memory/category.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Element-wise operations go to transform
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)(N0)(A1)(T1)(N1)
                            , ((node_<A0, elementwise_<T0>, N0, nt2::container::domain>))
                              ((node_<A1, elementwise_<T1>, N1, nt2::container::domain>))
                            )
  {
    typedef A0&                                             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      a0.resize(a1.extent());
      nt2::transform(container::as_view(a0), a1);
      return a0;
    }
  };

  //============================================================================
  // Copies go to transform as well, but we check for self-assignment.
  // This is not a pessimization, some code patterns rely on this!
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                            , (A0)(T0)
                            , ((node_ < A0, elementwise_<T0>
                                      , boost::mpl::long_<0>
                                      , nt2::container::domain
                                      >
                              ))
                              ((node_ < A0, elementwise_<T0>
                                      , boost::mpl::long_<0>
                                      , nt2::container::domain
                                      >
                              ))
                            )
  {
    typedef A0&                                             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A0& a1) const
    {
      a0.resize(a1.extent());
      if(a0.raw() != a1.raw()) nt2::transform(container::as_view(a0), a1);
      return a0;
    }
  };
} }

#endif
